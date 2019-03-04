#include <cassert>

#include "list_track.h"

#include "obj_track.h"

#include "obj_subject.h"

#include "list_add_event.h"
#include "list_remove_event.h"
#include "list_move_event.h"
#include "list_clear_event.h"

#include "obj.h"

#include "list.h"

#include "list_track_info.h"

#include "mimicry_info.h"

#include "list_mimic.h"

namespace telimtmsd {

ListTrack::ListTrack(
		ObjTrack* objTrack,
		List* list,
		ListTrackInfo const* trackInfo
		) :
	ContTrack(objTrack),
	m_cont(list),
	m_trackInfo(trackInfo)
{
}

ListTrack::~ListTrack()
{
	assert(m_tracks.empty());
}

const TrackInfo *ListTrack::trackInfo() const
{
	return m_trackInfo;
}

const ContTrackInfo *ListTrack::contTrackInfo() const
{
	return m_trackInfo;
}

Cont *ListTrack::cont() const
{
	return m_cont;
}

const ListTrackInfo *ListTrack::listTrackInfo() const
{
	return m_trackInfo;
}

List *ListTrack::list() const
{
	return m_cont;
}

size_t ListTrack::itemTracksSize() const
{
	return m_tracks.size();
}

ItemTrack *ListTrack::itemTrack(size_t index)
{
	auto const iter = std::next(m_tracks.begin(), index);
	return (*iter).get();
}

void ListTrack::forItemTracks(const std::function<bool (ItemTrack *, size_t)> &c)
{
	size_t i = 0;
	auto it = m_tracks.begin();
	bool resume = true;

	while ( resume && it != m_tracks.end() )
	{
		resume = c((*it).get(), i);

		++i;
		++it;
	}
}

void ListTrack::mimic(int key, MimicryInfo* mInfo)
{
	auto const mimic = toListMimic(mInfo->createMimic(m_trackInfo));
	mimic->setKey(key);
	mimic->setListTrack(this);
	m_mimics.emplace(key, MimicPack(mimic, mInfo));

	for ( auto const& track : m_tracks )
	{
		track->mimic(key, mInfo);
	}
}

void ListTrack::stopMimic(int key)
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimic(key);
	}

	m_mimics.erase(key);
}

void ListTrack::stopMimicAll()
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimicAll();
	}

	m_mimics.clear();
}

ListMimic*ListTrack::getListMimic(int key)
{
	return m_mimics.at(key).mimic.get();
}

Mimic*ListTrack::getMimic(int key)
{
	return getListMimic(key);
}

ContMimic *ListTrack::getContMimic(int key)
{
	return getListMimic(key);
}

void ListTrack::start_impl()
{
	objSubject()->listenCont(memberId(), [this](ContEvent const* e){handleContEvent(e);});
	catchUp();
}

void ListTrack::stop_impl()
{
	clear();
	objSubject()->stopListen(memberId());
}

void ListTrack::insert(Item *item, size_t index)
{
//	auto const subject = item->createSubject();
	auto const track = item->createTrack(
				this,
//				subject,
				m_trackInfo->itemTrackInfo(item->itemRtti())
				);

	auto const iter = std::next(m_tracks.begin(), index);

	m_tracks.emplace(iter, track);

	track->start();

	// Mimic
	for ( auto const& pair : m_mimics )
	{
		track->mimic(pair.first, pair.second.info);
	}
}

void ListTrack::remove(size_t index, size_t howMany)
{
	auto const rmBegin = std::next(m_tracks.begin(), index);
	auto const rmEnd = std::next(rmBegin, howMany);

	for ( auto i = rmBegin; i != rmEnd; ++i )
	{
		(*i)->stopMimicAll();
		(*i)->stop();
	}

	m_tracks.erase(rmBegin, rmEnd);
}

void ListTrack::move(size_t from, size_t howMany, size_t to)
{
	using Tracks = decltype(m_tracks);

	auto const mvBegin = std::next(m_tracks.begin(), from);
	auto const mvEnd = std::next(mvBegin, howMany);

	Tracks tmp(
				std::make_move_iterator(mvBegin),
				std::make_move_iterator(mvEnd)
				);
	m_tracks.erase(mvBegin, mvEnd);

	auto const mvTo = std::next(m_tracks.begin(), to);
	m_tracks.insert(
				mvTo,
				std::make_move_iterator(tmp.begin()),
				std::make_move_iterator(tmp.end())
				);
}

void ListTrack::catchUp()
{
	auto lamb = [this](Item* item, size_t index)->bool
	{
		(void)index;

		auto const track = item->createTrack(
					this,
					m_trackInfo->itemTrackInfo(item->itemRtti())
					);

		m_tracks.emplace_back(track);

		track->start();

		return true;
	};
	m_cont->forItems(std::cref(lamb));
}

void ListTrack::clear()
{
	for ( auto const& track : m_tracks )
	{
		track->stopMimicAll();
		track->stop();
	}
	m_tracks.clear();
}

void ListTrack::handleContEvent(const ContEvent *event_)
{
	auto const event = toListEvent(event_);
	switch ( event->type() )
	{
		using E = ListEvent::Type;
		case E::Add_B:
		{
			auto const e = toListAddEvent(event);

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_add_b(e->index(), objSubject() == event->subject());
			}
		}
			break;
		case E::Add_A:
		{
			auto const e = toListAddEvent(event);
			insert(e->newItem(), e->index());

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_add_a(e->index(), objSubject() == event->subject());
			}
		}break;
		case E::Remove_B:
		{
			auto const e = toListRemoveEvent(event);

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_remove_b(e->index(), e->howMany(), objSubject() == event->subject());
			}

			remove(e->index(), e->howMany());
		}break;
		case E::Remove_A:
		{
			auto const e = toListRemoveEvent(event);

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_remove_a(e->index(), e->howMany(), objSubject() == event->subject());
			}
		}
			break;
		case E::Move_B:
		{
			auto const e = toListMoveEvent(event);

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_move_b(e->from(), e->howMany(), e->to(), objSubject() == event->subject());
			}
		}
			break;
		case E::Move_A:
		{
			auto const e = toListMoveEvent(event);

			move(e->from(), e->howMany(), e->to());

			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_move_a(e->from(), e->howMany(), e->to(), objSubject() == event->subject());
			}
		}break;
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

//void ListTrack::FreeSubject::operator ()(ItemSubject *subject) const
//{
//	subject->freeThis();
//}

ListTrack::MimicPack::MimicPack(ListMimic* mimic, MimicryInfo* info) :
	mimic(mimic), info(info) {}


}
