#pragma once
#include "single_event.h"

namespace telimtmsd {

class SingleValidSetEvent final : public SingleEvent
{
public:
	SingleValidSetEvent(
			Single* single,
			ObjSubject* subject,
			Item* newItem) :
		SingleEvent(single, subject),
		m_newItem(newItem)
	{
	}

	auto newItem() const { return m_newItem; }

private:
	Item* m_newItem;
};

template <typename T>
inline SingleValidSetEvent const* toSingleValidSetEvent(T const* event) { return static_cast<SingleValidSetEvent const*>(event); }

}
