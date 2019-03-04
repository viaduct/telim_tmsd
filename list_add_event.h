#pragma once
#include <cstddef>
#include "list_event.h"

namespace telimtmsd {

class ListAddEvent final : public ListEvent
{
public:
	ListAddEvent(
			List* list,
			ObjSubject* subject,
			Item* newItem,
			size_t index
			) :
		ListEvent(list, subject),
		m_newItem(newItem),
		m_index(index)
	{
	}

	Item* newItem() const { return m_newItem; }
	auto index() const { return m_index; }

private:
	Item* m_newItem;
	size_t m_index;
};

template <typename T>
inline ListAddEvent const* toListAddEvent(T event) { return static_cast<ListAddEvent const*>(event); }

}
