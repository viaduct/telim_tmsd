#pragma once
#include "value.h"

#include "value_set_event.h"
#include "item_event.h"

#include "value_subject.tpp"

#include "value_track.tpp"

#include "item_track_info.h"
#include "value_track_info.h"

#include "value_type.h"

#include "value_stop_refer_info.h"

namespace telimtmsd {

template<typename T>
Value<T>::Value(
		Manager* manager,
		ValueType<T> const* valueType
		) :
	Item(manager),
	m_valueType(valueType)
{
}

template<typename T>
Value<T>::~Value()
{
}

template<typename T>
void Value<T>::stopRefer(Item*,StopReferInfo** sri)
{
	if ( sri )
	{
		auto const newSri = new ValueStopReferInfo;
		*sri = newSri;
	}
}

template<typename T>
void Value<T>::stopReferAll(StopReferInfo** sri)
{
	if ( sri )
	{
		auto const newSri = new ValueStopReferInfo;
		*sri = newSri;
	}
}

template<typename T>
size_t Value<T>::referredItemsSize() const
{
	return 0;
}

template<typename T>
std::vector<Item *> Value<T>::referredItems() const
{
	return std::vector<Item*>();
}

template <typename T>
ItemTrack* Value<T>::createTrack(
		Track* parent,
		ItemTrackInfo const* trackInfo
		)
{
	return new ValueTrack<T>(
				parent,
				this,
				toValueTrackInfo<T>(trackInfo)
				);
}

template<typename T>
const ItemType *Value<T>::itemType() const
{
	return m_valueType;
}

template<typename T>
ValueType<T> const* Value<T>::valueType() const
{
	return m_valueType;
}

template<typename T>
const T &Value<T>::get() const
{
	return m_value;
}

template<typename T>
void Value<T>::set(ValueSubject<T> *subject, T t)
{
	ValueSetEvent<T> e(
				this,
				subject,
				m_value,
				t
				);

	e.setType(decltype(e)::Type::Set_B);
	for ( auto const& subject : m_subjects ) { subject->emitEvent(&e); }

	m_value = std::move(t);

	e.setType(decltype(e)::Type::Set_A);
	for ( auto const& subject : m_subjects ) { subject->emitEvent(&e); }
}

template<typename T>
ValueSubject<T> *Value<T>::createValueSubject()
{
	auto const iter = m_subjects.emplace(std::make_unique<ValueSubject<T>>(this)).first;
	return (*iter).get();
}

template<typename T>
void Value<T>::freeValueSubject(ValueSubject<T> *subject)
{
	subject->emitExpired();
	m_subjects.erase(m_subjects.find(subject));
}

template<typename T>
void Value<T>::handleItemEvent(const ItemEvent * event)
{
	switch ( event->type() )
	{
		case ItemEvent::Type::Expire_B:
			freeAllValueSubjects();
			break;
		default:
			break;
	}
}

template<typename T>
void Value<T>::freeAllValueSubjects()
{
	for ( auto const& subject : m_subjects )
	{
		subject->emitExpired();
	}
	m_subjects.clear();
}

}
