#include "single.h"

#include "single_valid_set_event.h"
#include "single_null_set_event.h"

#include "obj.h"

#include "single_stop_refer_info.h"

#include "single_track.h"

#include "single_type.h"

#include "single_track_info.h"

namespace telimtmsd {

Single::Single(Obj* obj, SingleType const* singleType) :
	Cont(obj),
	m_singleType(singleType)
{
}

Single::~Single()
{
}

void Single::stopRefer(Item *item, ContStopReferInfo** sri)
{
	auto const newSri = new SingleStopReferInfo;
	newSri->setSingle(this);
	if ( get() == item )
	{
		newSri->setTarget(get());
	}

	*sri = newSri;
}

void Single::stopReferAll(ContStopReferInfo** sri)
{
	auto const newSri = new SingleStopReferInfo;
	newSri->setSingle(this);
	newSri->setTarget(get());

	*sri = newSri;
}

ContTrack* Single::createContTrack(
		ObjTrack* parent,
		ContTrackInfo const* trackInfo
		)
{
	return new SingleTrack(
				parent,
				this,
				toSingleTrackInfo(trackInfo)
				);
}

size_t Single::referredItemsSize() const
{
	return isValid() ? 1 : 0;
}

void Single::referredItems(std::vector<Item *> *out) const
{
	if ( isValid() )
	{
		out->push_back(get());
	}
}

ContType const* Single::contType() const
{
	return m_singleType;
}

const SingleType *Single::singleType() const
{
	return m_singleType;
}

void Single::setDefaultItem(Item* item)
{
	setValid(nullptr, item);
}

bool Single::isValid() const
{
	return m_item;
}

Item *Single::get() const
{
	return m_item;
}

void Single::setValid(ObjSubject *subject, Item *one)
{
	SingleValidSetEvent e(
				this,
				subject,
				one
				);

	e.setType(decltype(e)::Type::ValidSet_B);
	emitEvent(&e);

	m_item = one;
	obj()->emitRefer(m_item);

	e.setType(decltype(e)::Type::ValidSet_A);
	emitEvent(&e);
}

void Single::setNull(ObjSubject *subject)
{
	SingleNullSetEvent e(
				this,
				subject,
				m_item
				);

	e.setType(decltype(e)::Type::NullSet_B);
	emitEvent(&e);

	obj()->emitStopRefer(m_item);
	m_item = nullptr;

	e.setType(decltype(e)::Type::NullSet_A);
	emitEvent(&e);
}

}
