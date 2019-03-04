#pragma once
#include "single_event.h"

namespace telimtmsd {

class SingleNullSetEvent final : public SingleEvent
{
public:
	SingleNullSetEvent(
			Single* single,
			ObjSubject* subject,
			Item* oldItem) :
		SingleEvent(single, subject),
		m_oldItem(oldItem)
	{
	}

	auto oldItem() const { return m_oldItem; }

private:
	Item* m_oldItem;
};

}
