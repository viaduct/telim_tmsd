#pragma once
#include "value_event.h"

namespace telimtmsd {

template <typename T>
class ValueSetEvent final : public ValueEvent<T>
{
public:
	ValueSetEvent(
			Value<T>* value,
			ValueSubject<T>* subject,
			T oldValue,
			T newValue) :
		ValueEvent<T>(value, subject),
		m_old(oldValue),
		m_new(newValue)
	{
	}

	auto const& oldValue() const { return m_old; }
	auto const& newValue() const { return m_new; }

private:
	T m_old, m_new;
};

template <typename... Args, typename T>
inline ValueSetEvent<Args...>* toValueSetEvent(T* one) { return static_cast<ValueSetEvent<Args...>*>(one); }

using IntValueSetEvent = ValueSetEvent<IntValueAlias>;
using FloatValueSetEvent = ValueSetEvent<FloatValueAlias>;
using StringValueSetEvent = ValueSetEvent<StringValueAlias>;
using BoolValueSetEvent = ValueSetEvent<BoolValueAlias>;

}
