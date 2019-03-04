#include "set.h"

#include "set_add_event.h"
#include "set_remove_event.h"
#include "set_clear_event.h"

#include "obj.h"

#include "set_stop_refer_info.h"

#include "set_type.h"

#include "set_track_info.h"

#include "set_track.h"

namespace telimtmsd {

Set::Set(Obj* obj, SetType const* setType) :
	Cont(obj), m_setType(setType)
{
}

Set::~Set()
{
}

void Set::stopRefer(Item* item, ContStopReferInfo** sri)
{
	auto const iter = m_items.find(item);
	auto const hasItem = iter != m_items.end();

	auto const newSri = new SetStopReferInfo;
	newSri->setSet(this);
	if ( hasItem ) { newSri->reserve(1); }
	newSri->add(*iter);

	*sri = newSri;
}

void Set::stopReferAll(ContStopReferInfo** sri)
{
	auto const newSri = new SetStopReferInfo;
	newSri->setSet(this);
	newSri->reserve(m_items.size());
	for ( auto i = m_items.begin(); i != m_items.end(); ++i )
	{
		newSri->add(*i);
	}

	*sri = newSri;
}

size_t Set::referredItemsSize() const
{
	return m_items.size();
}

void Set::referredItems(std::vector<Item*>* out) const
{
	for ( Item* one : m_items )
	{
		out->push_back(one);
	}
}

ContTrack*Set::createContTrack(ObjTrack* parent, const ContTrackInfo* trackInfo)
{
	return new SetTrack(
				parent,
				this,
				toSetTrackInfo(trackInfo)
				);
}

ContType const* Set::contType() const
{
	return m_setType;
}

const SetType *Set::setType() const
{
	return m_setType;
}

bool Set::isEmpty() const
{
	return m_items.empty();
}

size_t Set::size() const
{
	return m_items.size();
}

void Set::forItems(const std::function<bool (Item *)> &c) const
{
	bool resume = true;
	for ( auto i = m_items.begin(); resume && i != m_items.end(); ++i )
	{
		resume = c(*i);
	}
}

bool Set::add(ObjSubject *subject, Item *item)
{
	return add_intern(subject, item).second;
}

bool Set::remove(ObjSubject *subject, Item *item)
{
	return remove_intern(subject, item);
}

void Set::clear(ObjSubject *subject)
{
	SetClearEvent e(this, subject);

	e.setType(decltype(e)::Type::Clear_B);
	emitEvent(&e);

	for ( Item* item : m_items )
	{
		obj()->emitStopRefer(item);
	}
	m_items.clear();

	e.setType(decltype(e)::Type::Clear_A);
	emitEvent(&e);
}

std::pair<Set::Iter, bool> Set::add_intern(ObjSubject *subject, Item *item)
{
	auto const iter = m_items.find(item);
	if ( iter == m_items.end() )
	{
		SetAddEvent e(
					this,
					subject,
					item
					);

		e.setType(decltype(e)::Type::Add_B);
		emitEvent(&e);

		auto const result = m_items.insert(item);
		obj()->emitRefer(item);

		e.setType(decltype(e)::Type::Add_A);
		emitEvent(&e);

		return result;
	}
	else
	{
		return std::pair<Iter, bool>(iter, false);
	}
}

bool Set::remove_intern(ObjSubject *subject, Item *item)
{
	auto const iter = m_items.find(item);
	if ( iter != m_items.end() )
	{
		remove_intern(subject, iter);
		return true;
	}
	else
	{
		return false;
	}
}

Set::Iter Set::remove_intern(ObjSubject *subject, Set::CIter iter)
{
	SetRemoveEvent e(this, subject, *iter);

	e.setType(decltype(e)::Type::Remove_B);
	emitEvent(&e);

	obj()->emitStopRefer(*iter);
	auto const result = m_items.erase(iter);

	e.setType(decltype(e)::Type::Remove_A);
	emitEvent(&e);

	return result;
}

}
