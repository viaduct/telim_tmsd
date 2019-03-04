#include <cassert>

#include "single_track.h"

#include "obj_track.h"

#include "obj_subject.h"

#include "single_valid_set_event.h"
#include "single_null_set_event.h"

#include "obj.h"

#include "single.h"

#include "single_track_info.h"

#include "mimicry_info.h"

#include "single_mimic.h"

namespace telimtmsd {

SingleTrack::SingleTrack(
		ObjTrack* objTrack,
		Single* single,
		SingleTrackInfo const* trackInfo
		) :
	ContTrack(objTrack),
	m_cont(single),
	m_trackInfo(trackInfo)
{
}

SingleTrack::~SingleTrack()
{
	assert(isItemTrackValid() == false);
}

const TrackInfo *SingleTrack::trackInfo() const
{
	return m_trackInfo;
}

const ContTrackInfo *SingleTrack::contTrackInfo() const
{
	return m_trackInfo;
}

Cont *SingleTrack::cont() const
{
	return m_cont;
}

const SingleTrackInfo *SingleTrack::singleTrackInfo() const
{
	return m_trackInfo;
}

Single *SingleTrack::single() const
{
	return m_cont;
}

bool SingleTrack::isItemTrackValid() const
{
	return (bool)m_track;
}

ItemTrack *SingleTrack::itemTrack()
{
	return m_track.get();
}

void SingleTrack::mimic(int key, MimicryInfo *mInfo)
{
	auto const mimic = toSingleMimic(mInfo->createMimic(m_trackInfo));
	mimic->setKey(key);
	mimic->setSingleTrack(this);
	m_mimics.emplace(key, MimicPack(mimic, mInfo));

	m_track->mimic(key, mInfo);
}

void SingleTrack::stopMimic(int key)
{
	m_track->stopMimic(key);

	m_mimics.erase(key);
}

void SingleTrack::stopMimicAll()
{
	m_track->stopMimicAll();

	m_mimics.clear();
}

SingleMimic*SingleTrack::getSingleMimic(int key)
{
	return m_mimics.at(key).mimic.get();
}

Mimic*SingleTrack::getMimic(int key)
{
	return getSingleMimic(key);
}

ContMimic *SingleTrack::getContMimic(int key)
{
	return getSingleMimic(key);
}

void SingleTrack::start_impl()
{
	objSubject()->listenCont(memberId(), [this](ContEvent const* e){handleContEvent(e);});
	if ( m_cont->isValid() )
	{
		setValidItemTrack(m_cont->get());
	}
}

void SingleTrack::stop_impl()
{
	if ( isItemTrackValid() )
	{
		setNullItemTrack();
	}
	objSubject()->stopListen(memberId());
}

void SingleTrack::handleContEvent(const ContEvent *event_)
{
	auto const event = toSingleEvent(event_);
	switch ( event->type() )
	{
		using E = SingleEvent::Type;
		case E::ValidSet_B:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_validSet_b(objSubject() == event->subject());
			}
			break;
		case E::ValidSet_A:
		{
			auto const e = toSingleValidSetEvent(event);
			setValidItemTrack(e->newItem());

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_validSet_a(objSubject() == event->subject());
			}
		}break;
		case E::NullSet_B:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_nullSet_b(objSubject() == event->subject());
			}

			setNullItemTrack();
			break;
		case E::NullSet_A:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_nullSet_a(objSubject() == event->subject());
			}
			break;
		default:
			break;
	}
}

void SingleTrack::setValidItemTrack(Item* item)
{
	m_track.reset(
				item->createTrack(
					this,
					m_trackInfo->itemTrackInfo(item->itemRtti())
					)
				);
	m_track->start();
	// Mimic
	for ( auto const& pair : m_mimics )
	{
		m_track->mimic(pair.first, pair.second.info);
	}
}

void SingleTrack::setNullItemTrack()
{
	m_track->stopMimicAll();
	m_track->stop();
	m_track.reset();
}

SingleTrack::MimicPack::MimicPack(SingleMimic *mimic, MimicryInfo *info) :
	mimic(mimic), info(info) {}

}
