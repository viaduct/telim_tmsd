#include "obj_mimic.h"

#include "obj_track.h"

#include "cont_track.h"

#include "cont_mimic.h"

namespace telimtmsd {

Track *ObjMimic::track() const
{
	return m_track;
}

ItemTrack *ObjMimic::itemTrack() const
{
	return m_track;
}

void ObjMimic::setObjTrack(ObjTrack *one)
{
	m_track = one;
}

ObjTrack *ObjMimic::objTrack() const
{
	return m_track;
}

Obj *ObjMimic::obj() const
{
	return m_track->obj();
}

ContMimic*ObjMimic::contMimic(MemberId mid) const
{
	return toContMimic(m_track->contTrack(mid)->getMimic(key()));
}

ContMimic*ObjMimic::contMimic_safe(MemberId mid) const
{
	return toContMimic(m_track->contTrack_safe(mid)->getMimic(key()));
}

bool ObjMimic::hasContMimic(MemberId mid) const
{
	return m_track->hasContTrack(mid);
}

void ObjMimic::forContMimics(const std::function<bool (MemberId, ContMimic *)> &c) const
{
	auto l = [&c, key = this->key()](MemberId mid, ContTrack* const track)->bool
	{
		return c(mid, track->getContMimic(key));
	};
	m_track->forContTracks(std::cref(l));
}

std::vector<std::tuple<MemberId, ContMimic *> > ObjMimic::contMimics() const
{
	std::vector<std::tuple<MemberId, ContMimic*>> r;
	r.reserve(objTrack()->contTracksSize());
	for ( auto const& tup : objTrack()->contTracks() )
	{
		r.emplace_back(std::get<0>(tup), std::get<1>(tup)->getContMimic(key()));
	}
	return r;
}

size_t ObjMimic::contMimicsSize() const
{
	return objTrack()->contTracksSize();
}

ContMimic *ObjMimic::child(MemberId mid) const
{
	return contMimic(mid);
}

ContMimic *ObjMimic::child_safe(MemberId mid) const
{
	return contMimic_safe(mid);
}

bool ObjMimic::hasChild(MemberId mid) const
{
	return hasContMimic(mid);
}

std::vector<std::tuple<MemberId, ContMimic *> > ObjMimic::children() const
{
	return contMimics();
}

size_t ObjMimic::childrenSize() const
{
	return contMimicsSize();
}

}
