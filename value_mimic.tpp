#pragma once
#include "value_mimic.h"

#include "value_track.h"

#include "value_subject.h"

#include "value.tpp"

namespace telimtmsd {

template<typename T>
Track *ValueMimic<T>::track() const
{
	return m_track;
}

template<typename T>
ItemTrack *ValueMimic<T>::itemTrack() const
{
	return m_track;
}

template<typename T>
void ValueMimic<T>::setValueTrack(ValueTrack<T> *one)
{
	m_track = one;
}

template<typename T>
ValueTrack<T> *ValueMimic<T>::valueTrack() const
{
	return m_track;
}

template<typename T>
ValueSubject<T> *ValueMimic<T>::valueSubject() const
{
	return valueTrack()->valueSubject();
}

template<typename T>
Value<T> *ValueMimic<T>::value() const
{
	return m_track->value();
}

template<typename T>
const T &ValueMimic<T>::get() const
{
	return m_track->value()->get();
}

template<typename T>
void ValueMimic<T>::set(T value) const
{
	this->value()->set(valueSubject(), value);
}

template<typename T>
void ValueMimic<T>::emit_set_b(bool fromThis)
{
	handle_set_b(fromThis);
}

template<typename T>
void ValueMimic<T>::emit_set_a(bool fromThis)
{
	handle_set_a(fromThis);
}

template<typename T>
void ValueMimic<T>::handle_set_b(bool fromThis)
{
	(void)fromThis;
}

template<typename T>
void ValueMimic<T>::handle_set_a(bool fromThis)
{
	(void)fromThis;
}

}
