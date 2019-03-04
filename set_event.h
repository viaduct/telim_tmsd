#pragma once
#include "cont_event.h"

namespace telimtmsd {

class Item;
class Set;
class ObjSubject;

class SetEvent : public ContEvent
{
public:
	enum class Type : char
	{
		Add_B,
		Add_A,
		Remove_B,
		Remove_A,
		Clear_B,
		Clear_A
	};

	SetEvent(Set* set, ObjSubject* subject) :
		m_set(set), m_subject(subject)
	{
	}

	Type type() const { return m_type; }
	void setType(Type value) { m_type = value; }

	auto set() const { return m_set; }
	auto subject() const { return m_subject; }
	bool isFromSubject() const { return m_subject; }

private:
	Set* m_set;
	ObjSubject* m_subject;
	Type m_type;
};

template <typename T>
inline SetEvent const* toSetEvent(T const* one) { return static_cast<SetEvent const*>(one); }

}
