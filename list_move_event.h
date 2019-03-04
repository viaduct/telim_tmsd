#pragma once
#include <cstddef>
#include "list_event.h"

namespace telimtmsd {

class ListMoveEvent final : public ListEvent
{
public:
	ListMoveEvent(
			List* list,
			ObjSubject* subject,
			size_t from,
			size_t howMany,
			size_t to
			) :
		ListEvent(list, subject),
		m_from(from),
		m_howMany(howMany),
		m_to(to)
	{
	}

	auto from() const { return m_from; }
	auto howMany() const { return m_howMany; }
	auto to() const { return m_to; }

private:
	size_t m_from, m_howMany, m_to;
};

template <typename T>
inline ListMoveEvent const* toListMoveEvent(T event) { return static_cast<ListMoveEvent const*>(event); }

}
