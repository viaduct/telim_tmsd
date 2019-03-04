#pragma once
#include "value_alias.h"

namespace telimtmsd {

template <typename T> class Value;
template <typename T> class ValueSubject;

enum class ValueEventType : char
{
	Set_B,
	Set_A
};

template <typename T>
class ValueEvent
{
public:
	using Type = ValueEventType;

	ValueEvent(Value<T>* value, ValueSubject<T>* subject) :
		m_value(value),
		m_subject(subject)
	{
	}

	void setType(Type value) { m_type = value; }
	Type type() const { return m_type; }

	auto value() const { return m_value; }
	auto subject() const { return m_subject; }
	bool isFromSubject() const { return m_subject; }

private:
	Value<T>* m_value;
	ValueSubject<T>* m_subject;
	Type m_type;
};

using IntValueEvent = ValueEvent<IntValueAlias>;
using FloatValueEvent = ValueEvent<FloatValueAlias>;
using StringValueEvent = ValueEvent<StringValueAlias>;
using BoolValueEvent = ValueEvent<BoolValueAlias>;

}
