#include <cassert>

#include "set_track.h"

#include "obj_track.h"

#include "obj_subject.h"

#include "set_add_event.h"
#include "set_remove_event.h"
#include "set_clear_event.h"

#include "obj.h"

#include "set.h"

#include "set_track_info.h"

#include "mimicry_info.h"

#include "set_mimic.h"

namespace telimtmsd {

SetTrack::SetTrack(
		ObjTrack* objTrack,
		Set* set,
		SetTrackInfo const* trackInfo
		) :
	ContTrack(objTrack),
	m_cont(set),
	m_trackInfo(trackInfo)
{
}

SetTrack::~SetTrack()
{
	assert(m_tracks.empty());
}

const TrackInfo *SetTrack::trackInfo() const
{
	return m_trackInfo;
}

const ContTrackInfo *SetTrack::contTrackInfo() const
{
	return m_trackInfo;
}

Cont *SetTrack::cont() const
{
	return m_cont;
}

const SetTrackInfo *SetTrack::setTrackInfo() const
{
	return m_trackInfo;
}

Set *SetTrack::set() const
{
	return m_cont;
}

size_t SetTrack::itemTracksSize() const
{
	return m_tracks.size();
}

ItemTrack *SetTrack::itemTrack(size_t index)
{
	auto const iter = std::next(m_tracks.begin(), index);
	return (*iter).get();
}

ItemTrack *SetTrack::itemTrack(const Item *item)
{
	for ( auto const& track : m_tracks )
	{
		if ( track->item() == item )
		{
			return track.get();
		}
	}
	return nullptr;
}

bool SetTrack::hasItemTrack(const Item *item) const
{
	return const_cast<SetTrack*>(this)->itemTrack(item) != nullptr;
}

void SetTrack::forItemTracks(const std::function<bool (ItemTrack *, size_t)> &c)
{
	size_t i = 0 ;
	auto it = m_tracks.begin();
	bool resume = true;

	while ( resume && it != m_tracks.end() )
	{
		resume = c((*it).get(), i);

		++it;
		++i;
	}
}

void SetTrack::mimic(int key, MimicryInfo *mInfo)
{
	auto const mimic = toSetMimic(mInfo->createMimic(m_trackInfo));
	mimic->setKey(key);
	mimic->setSetTrack(this);
	m_mimics.emplace(key, MimicPack(mimic, mInfo));

	for ( auto const& track : m_tracks )
	{
		track->mimic(key, mInfo);
	}
}

void SetTrack::stopMimic(int key)
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimic(key);
	}

	m_mimics.erase(key);
}

void SetTrack::stopMimicAll()
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimicAll();
	}

	m_mimics.clear();
}

SetMimic*SetTrack::getSetMimic(int key)
{
	return m_mimics.at(key).mimic.get();
}

Mimic*SetTrack::getMimic(int key)
{
	return getSetMimic(key);
}

ContMimic *SetTrack::getContMimic(int key)
{
	return getSetMimic(key);
}

void SetTrack::start_impl()
{
	objSubject()->listenCont(memberId(), [this](ContEvent const* e){handleContEvent(e);});
	catchUp();
}

void SetTrack::stop_impl()
{
	clear();
	objSubject()->stopListen(memberId());
}

void SetTrack::append(Item *item)
{
	auto const track = item->createTrack(
				this,
				m_trackInfo->itemTrackInfo(item->itemRtti())
				);
	m_tracks.emplace_back(track);
	track->start();

	// Mimic
	for ( auto const& pair : m_mimics )
	{
		track->mimic(pair.first, pair.second.info);
	}
}

void SetTrack::remove(Tracks::const_iterator i)
{
	(*i)->stopMimicAll();
	(*i)->stop();
	m_tracks.erase(i);
}

void SetTrack::loc(Item* item, Tracks::const_iterator* iterOut, size_t* indexOut) const
{
	size_t i = 0;
	auto it = m_tracks.begin();

	while ( it != m_tracks.end() )
	{
		if ( (*it)->item() == item )
		{
			*iterOut = it;
			*indexOut = i;
		}

		++i;
		++it;
	}

	assert(false);
}

void SetTrack::catchUp()
{
	{
		auto l = [this](Item* item)->bool
		{
			auto const track = item->createTrack(
						this,
						m_trackInfo->itemTrackInfo(item->itemRtti())
						);
			m_tracks.emplace_back(track);
			track->start();
			return true;
		};
		m_cont->forItems(std::cref(l));
	}
}

void SetTrack::clear()
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimicAll();
		track->stop();
	}
	m_tracks.clear();
}

void SetTrack::handleContEvent(ContEvent const* event_)
{
	auto const event = toSetEvent(event_);
	switch ( event->type() )
	{
		using E = SetEvent::Type;
		case E::Add_B:
		{
			m_addIndex = m_tracks.size();
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_add_b(m_addIndex, objSubject() == event->subject());
			}
		}break;
		case E::Add_A:
		{
			auto const e = toSetAddEvent(event);
			append(e->newItem());

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_add_a(m_addIndex, objSubject() == event->subject());
			}
		}break;
		case E::Remove_B:
		{
			auto const e = toSetRemoveEvent(event);

			Tracks::const_iterator it;
			loc(e->oldItem(), &it, &m_removeIndex);

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_remove_b(m_removeIndex, objSubject() == event->subject());
			}

			remove(it);
		}break;
		case E::Remove_A:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_remove_a(m_removeIndex, objSubject() == event->subject());
			}
			break;
		case E::Clear_B:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_clear_b(objSubject() == event->subject());
			}

			clear();
			break;
		case E::Clear_A:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_clear_a(objSubject() == event->subject());
			}
			break;
		default:
			break;
	}
}

//void SetTrack::FreeSubject::operator ()(ItemSubject *subject) const
//{
//	subject->freeThis();
//}

SetTrack::MimicPack::MimicPack(SetMimic *mimic, MimicryInfo *info) :
	mimic(mimic), info(info) {}

}
