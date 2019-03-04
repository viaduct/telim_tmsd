#pragma once
#include "value_track.h"

#include "value.h"

#include "value_subject.h"

#include "value_mimic.h"

#include "mimicry_info.h"

#include "value_set_event.h"

namespace telimtmsd {

template<typename T>
ValueTrack<T>::ValueTrack(
		Track* parent,
		Value<T>* value,
		ValueTrackInfo<T> const* trackInfo
		) :
	ItemTrack(parent),
	m_value(value),
	m_trackInfo(trackInfo)
{
}

template<typename T>
const TrackInfo *ValueTrack<T>::trackInfo() const
{
	return m_trackInfo;
}

template<typename T>
const ItemTrackInfo *ValueTrack<T>::itemTrackInfo() const
{
	return m_trackInfo;
}

template<typename T>
Item *ValueTrack<T>::item() const
{
	return value();
}

template<typename T>
const ValueTrackInfo<T> *ValueTrack<T>::valueTrackInfo() const
{
	return m_trackInfo;
}

template<typename T>
ValueSubject<T> *ValueTrack<T>::valueSubject() const
{
	return m_subject;
}

template<typename T>
Value<T> *ValueTrack<T>::value() const
{
	return m_value;
}

template<typename T>
void ValueTrack<T>::mimic(int key, MimicryInfo *mInfo)
{
	auto const mimic = toValueMimic<T>(mInfo->createMimic(m_trackInfo));
	mimic->setKey(key);
	mimic->setValueTrack(this);
	m_mimics.emplace(key, MimicPack(mimic, mInfo));
}

template<typename T>
void ValueTrack<T>::stopMimic(int key)
{
	m_mimics.erase(key);
}

template<typename T>
void ValueTrack<T>::stopMimicAll()
{
	m_mimics.clear();
}

template<typename T>
ValueMimic<T>*ValueTrack<T>::getValueMimic(int key)
{
	return m_mimics.at(key).mimic.get();
}

template<typename T>
Mimic*ValueTrack<T>::getMimic(int key)
{
	return getValueMimic(key);
}

template<typename T>
ItemMimic *ValueTrack<T>::getItemMimic(int key)
{
	return getValueMimic(key);
}

template<typename T>
void ValueTrack<T>::start_impl()
{
	m_subject = value()->createValueSubject();
	valueSubject()->listen([this](ValueEvent<T> const* event){handleValueEvent(event);});
}

template<typename T>
void ValueTrack<T>::stop_impl()
{
	valueSubject()->stopListen();
	value()->freeValueSubject(m_subject);
}

template <typename T>
void ValueTrack<T>::handleValueEvent(ValueEvent<T> const* event)
{
	switch ( event->type() )
	{
		using E = ValueEventType;
		case E::Set_B:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_set_b(m_subject == event->subject());
			}
			break;
		case E::Set_A:
			for ( auto const& pair : m_mimics )
			{
				pair.second.mimic->emit_set_a(m_subject == event->subject());
			}
			break;
		default:
			break;
	}
}

template<typename T>
ValueTrack<T>::MimicPack::MimicPack(ValueMimic<T> *mimic, MimicryInfo *info) :
	mimic(mimic), info(info) {}

}
