#pragma once
#include <cstddef>
#include "list_event.h"

namespace telimtmsd {

class ListRemoveEvent final : public ListEvent
{
public:
	ListRemoveEvent(
			List* list,
			ObjSubject* subject,
			size_t index,
			size_t howMany
			) :
		ListEvent(list, subject),
		m_index(index),
		m_howMany(howMany)
	{
	}

	auto index() const { return m_index; }
	auto howMany() const { return m_howMany; }

private:
	size_t m_index, m_howMany;
};

template <typename T>
inline ListRemoveEvent const* toListRemoveEvent(T event) { return static_cast<ListRemoveEvent const*>(event); }

}
