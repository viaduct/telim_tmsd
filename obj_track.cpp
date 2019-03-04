#include "obj_track.h"

#include "obj_subject.h"

#include "cont_track.h"

#include "obj.h"
#include "cont.h"

#include "obj_track_info.h"
#include "cont_track_info.h"

#include "obj_mimic.h"

#include "mimicry_info.h"

namespace telimtmsd {

ObjTrack::ObjTrack(
		Track* parent,
		Obj* obj,
		ObjTrackInfo const* trackInfo
		) :
	ItemTrack(parent),
	m_obj(obj),
	m_trackInfo(trackInfo)
{
}

ObjTrack::~ObjTrack()
{
}

const TrackInfo *ObjTrack::trackInfo() const
{
	return m_trackInfo;
}

const ItemTrackInfo *ObjTrack::itemTrackInfo() const
{
	return m_trackInfo;
}

Item *ObjTrack::item() const
{
	return obj();
}

const ObjTrackInfo *ObjTrack::objTrackInfo() const
{
	return m_trackInfo;
}

ObjSubject *ObjTrack::objSubject() const
{
	return m_subject;
}

Obj *ObjTrack::obj() const
{
	return m_obj;
}

ContTrack *ObjTrack::contTrack(MemberId mid)
{
	return m_contTracks.at(mid).get();
}

ContTrack *ObjTrack::contTrack_safe(MemberId mid)
{
	auto const iter = m_contTracks.find(mid);
	return (iter != m_contTracks.end()) ?
				(iter->second.get()) :
				(nullptr);
}

bool ObjTrack::hasContTrack(MemberId mid) const
{
	return m_contTracks.find(mid) != m_contTracks.end();
}

void ObjTrack::forContTracks(const std::function<bool (MemberId, ContTrack *)> &c)
{
	for ( auto const& pair : m_contTracks )
	{
		c(pair.first, pair.second.get());
	}
}

std::vector<std::tuple<MemberId, ContTrack *> > ObjTrack::contTracks()
{
	std::vector<std::tuple<MemberId, ContTrack*>> r;
	r.reserve(m_contTracks.size());
	for ( auto const& pair : m_contTracks )
	{
		r.emplace_back(pair.first, pair.second.get());
	}
	return r;
}

size_t ObjTrack::contTracksSize() const
{
	return m_contTracks.size();
}

void ObjTrack::mimic(int key, MimicryInfo *mInfo)
{
	auto const mimic = toObjMimic(mInfo->createMimic(m_trackInfo));
	mimic->setKey(key);
	mimic->setObjTrack(this);
	m_mimics.emplace(key, MimicPack(mimic, mInfo));

	for ( auto const& mid_contTrack : m_contTracks )
	{
		mid_contTrack.second->mimic(key, mInfo);
	}
}

void ObjTrack::stopMimic(int key)
{
	for ( auto const& mid_contTrack : m_contTracks )
	{
		mid_contTrack.second->stopMimic(key);
	}

	m_mimics.erase(key);
}

void ObjTrack::stopMimicAll()
{
	for ( auto const& mid_contTrack : m_contTracks )
	{
		mid_contTrack.second->stopMimicAll();
	}

	m_mimics.clear();
}

ObjMimic*ObjTrack::getObjMimic(int key)
{
	return m_mimics.at(key).mimic.get();
}

Mimic*ObjTrack::getMimic(int key)
{
	return getObjMimic(key);
}

ItemMimic *ObjTrack::getItemMimic(int key)
{
	return getObjMimic(key);
}

void ObjTrack::start_impl()
{
	m_subject = obj()->createObjSubject();
	// Catchup children tracks.
	{
		auto l = [this](ContTrackInfo const* info)->bool
		{
			auto const iter = m_contTracks.emplace(
						info->memberId(),
						obj()->cont(info->memberId())->createContTrack(
							this,
							info
							)
						).first;
			iter->second->start();
			return true;
		};
		m_trackInfo->forContTrackInfos(std::cref(l));
	}
}

void ObjTrack::stop_impl()
{
	for ( auto const& pair : m_contTracks )
	{
		pair.second->stopMimicAll();
		pair.second->stop();
	}
	m_contTracks.clear();
	obj()->freeObjSubject(m_subject);
}

ObjTrack::MimicPack::MimicPack(ObjMimic *mimic, MimicryInfo *info) :
	mimic(mimic), info(info) {}

}
