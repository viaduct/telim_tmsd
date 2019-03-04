#pragma once
#include "cont_event.h"

namespace telimtmsd {

class Item;
class Single;
class ObjSubject;

class SingleEvent : public ContEvent
{
public:
	enum class Type : char
	{
		ValidSet_B,
		ValidSet_A,
		NullSet_B,
		NullSet_A
	};

	SingleEvent(Single* single, ObjSubject* subject) :
		m_single(single), m_subject(subject)
	{
	}

	Type type() const { return m_type; }
	void setType(Type value) { m_type = value; }

	auto single() const { return m_single; }
	auto subject() const { return m_subject; }
	bool isFromSubject() const { return m_subject; }

private:
	Single* m_single;
	ObjSubject* m_subject;
	Type m_type;
};

template <typename T>
inline SingleEvent const* toSingleEvent(T const* one) { return static_cast<SingleEvent const*>(one); }

}
