#pragma once
#include "value_subject.h"

#include "value.h"

namespace telimtmsd {

//template<typename T>
//const T &ValueSubject<T>::get() const { return m_value->get(); }

//template<typename T>
//void ValueSubject<T>::set(T t) const { m_value->set(this, std::move(t)); }

template <typename T>
Item* ValueSubject<T>::item() const { return m_value; }

template<typename T>
void ValueSubject<T>::freeThis()
{
	m_value->freeValueSubject(this);
}

template<typename T>
void ValueSubject<T>::emitEvent(const ValueEvent<T> *event)
{
	if ( m_callback )
	{
		m_callback(event);
	}
}

template<typename T>
void ValueSubject<T>::listen(std::function<void (const ValueEvent<T> *)> callback)
{
	m_callback = std::move(callback);
}

template<typename T>
void ValueSubject<T>::stopListen()
{
	m_callback = nullptr;
}

}
