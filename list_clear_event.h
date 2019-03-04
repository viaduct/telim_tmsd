#pragma once
#include "list_event.h"

namespace telimtmsd {

class ListClearEvent final : public ListEvent
{
public:
	using ListEvent::ListEvent;
};

template <typename T>
inline ListClearEvent const* toListClearEvent(T event) { return static_cast<ListClearEvent const*>(event); }

}
