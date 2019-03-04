#include "list.h"

#include "list_add_event.h"
#include "list_remove_event.h"
#include "list_clear_event.h"
#include "list_move_event.h"

#include "obj.h"

#include "list_stop_refer_info.h"

#include "list_type.h"

#include "list_track.h"

#include "list_track_info.h"

namespace telimtmsd {

List::List(Obj* obj, ListType const* listType) :
	Cont(obj),
	m_listType(listType)
{
}

List::~List()
{
}

void List::stopRefer(Item* target, ContStopReferInfo** sri)
{
	auto const newSri = new ListStopReferInfo;
	newSri->setList(this);
	{
		auto lamb = [target, newSri](auto const item, auto const index)->bool
		{
			if ( target == item )
			{
				newSri->add(item, index);
			}
			return true;
		};
		forItems(std::cref(lamb));
	}

	*sri = newSri;
}

void List::stopReferAll(ContStopReferInfo** sri)
{
	auto const newSri = new ListStopReferInfo;
	newSri->setList(this);
	newSri->reserve(m_items.size());
	{
		auto l = [newSri](auto const item, auto const index)->bool
		{
			newSri->add(item, index);
			return true;
		};
		forItems(std::cref(l));
	}

	*sri = newSri;
}

size_t List::referredItemsSize() const
{
	return m_items.size();
}

void List::referredItems(std::vector<Item*>* out) const
{
	for ( Item* one : m_items )
	{
		out->push_back(one);
	}
}

ContTrack*List::createContTrack(ObjTrack* parent, const ContTrackInfo* trackInfo)
{
	return new ListTrack(
				parent,
				this,
				toListTrackInfo(trackInfo)
				);
}

ContType const* List::contType() const
{
	return m_listType;
}

const ListType *List::listType() const
{
	return m_listType;
}

bool List::isEmpty() const
{
	return m_items.empty();
}

size_t List::size() const
{
	return m_items.size();
}

void List::forItems(std::function<bool (Item*, size_t)> const& c) const
{
	size_t i = 0;
	auto iter = m_items.begin();

	bool resume = true;
	while ( resume && iter != m_items.end() )
	{
		resume = c(*iter, i);

		++i;
		++iter;
	}
}

//void List::forItems_r(std::function<bool (Item *, size_t)> const& c) const
//{
//	size_t i = m_items.size();
//	auto iter = m_items.end();

//	bool resume = true;
//	while ( resume && iter != m_items.begin() )
//	{
//		--i;
//		--iter;

//		resume = c(*iter, i);
//	}
//}

//void List::forMutItems(std::function<bool (Item*, size_t, PostAct*)> const& c)
//{
//	size_t i = 0;
//	auto iter = m_items.begin();

//	bool resume = true;
//	while ( resume && iter != m_items.end() )
//	{
//		PostAct act;
//		resume = c(*iter, i, &act);

//		switch ( act.code() )
//		{
//			case PostAct::DoRemove:
//				iter = remove_intern(act.subject(), iter, i);
//				break;
//			default:
//				break;
//		}

//		++i;
//		++iter;
//	}
//}

//void List::forMutItems_r(std::function<bool (Item*, size_t, PostAct*)> const& c)
//{
//	size_t i = m_items.size();
//	auto iter = m_items.end();

//	bool resume = true;
//	while ( resume && iter != m_items.begin() )
//	{
//		--i;
//		--iter;

//		PostAct act;
//		resume = c(*iter, i, &act);

//		switch ( act.code() )
//		{
//			case PostAct::DoRemove:
//				iter = remove_intern(act.subject(), iter, i);
//				break;
//			default:
//				break;
//		}
//	}
//}

void List::append(ObjSubject *subject, Item *item)
{
	ListAddEvent e(this, subject, item, m_items.size());

	e.setType(ListEvent::Type::Add_B);
	emitEvent(&e);

	m_items.push_back(item);
	obj()->emitRefer(item);

	e.setType(ListEvent::Type::Add_A);
	emitEvent(&e);
}

void List::insert(ObjSubject *subject, Item *item, size_t index)
{
	ListAddEvent e(this, subject, item, index);

	e.setType(ListEvent::Type::Add_B);
	emitEvent(&e);

	m_items.insert(std::next(m_items.begin(), index), item);
	obj()->emitRefer(item);

	e.setType(ListEvent::Type::Add_A);
	emitEvent(&e);
}

void List::move(ObjSubject *subject, size_t from, size_t howMany, size_t to)
{
	ListMoveEvent e(this, subject, from, howMany, to);

	e.setType(ListEvent::Type::Move_B);
	emitEvent(&e);

	auto const mvBegin = std::next(m_items.begin(), from);
	auto const mvEnd = std::next(mvBegin, howMany);

	Items tmp(
				std::make_move_iterator(mvBegin),
				std::make_move_iterator(mvEnd)
				);
	m_items.erase(mvBegin, mvEnd);

	auto const insertToHere = std::next(m_items.begin(), to);
	m_items.insert(
				insertToHere,
				std::make_move_iterator(tmp.begin()),
				std::make_move_iterator(tmp.end())
				);

	e.setType(ListEvent::Type::Move_A);
	emitEvent(&e);
}

void List::remove(ObjSubject *subject, size_t from, size_t howMany)
{
	ListRemoveEvent e(this, subject, from, howMany);

	e.setType(ListEvent::Type::Remove_B);
	emitEvent(&e);

	auto const rmBegin = std::next(m_items.begin(), from);
	auto const rmEnd = std::next(rmBegin, howMany);
	for ( auto i = rmBegin; i != rmEnd; ++i )
	{
		obj()->emitStopRefer(*i);
	}
	m_items.erase(rmBegin, rmEnd);

	e.setType(ListEvent::Type::Remove_A);
	emitEvent(&e);
}

void List::clear(ObjSubject* subject)
{
	ListClearEvent e(this, subject);

	e.setType(ListEvent::Type::Clear_B);
	emitEvent(&e);

	for ( Item* item : m_items )
	{
		obj()->emitStopRefer(item);
	}
	m_items.clear();

	e.setType(ListEvent::Type::Clear_A);
	emitEvent(&e);
}

List::Iter List::remove_intern(ObjSubject *subject, List::CIter iter, size_t index)
{
	ListRemoveEvent e(this, subject, index, 1);

	e.setType(decltype(e)::Type::Remove_B);
	emitEvent(&e);

	auto const result = m_items.erase(iter);

	e.setType(decltype(e)::Type::Remove_A);
	emitEvent(&e);

	return result;
}

//char List::PostAct::code() const
//{
//	return m_code;
//}

//ObjSubject *List::PostAct::subject() const
//{
//	return m_subject;
//}

//void List::PostAct::remove(ObjSubject *subject)
//{
//	m_subject = subject;
//	m_code = DoRemove;
//}

}
