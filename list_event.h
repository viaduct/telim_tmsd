#pragma once
#include "cont_event.h"

namespace telimtmsd {

class Item;
class List;
class ObjSubject;

class ListEvent : public ContEvent
{
public:
	enum class Type : char
	{
		Add_B,
		Add_A,
		Remove_B,
		Remove_A,
		Move_B,
		Move_A,
		Clear_B,
		Clear_A
	};

	ListEvent(List* list, ObjSubject* subject) :
		m_list(list), m_subject(subject)
	{
	}

	Type type() const { return m_type; }
	void setType(Type value) { m_type = value; }

	auto list() const { return m_list; }
	auto subject() const { return m_subject; }
	bool isFromSubject() const { return m_subject; }

private:
	List* m_list;
	ObjSubject* m_subject;
	Type m_type;
};

template <typename T>
inline ListEvent const* toListEvent(T const* one) { return static_cast<ListEvent const*>(one); }

}
