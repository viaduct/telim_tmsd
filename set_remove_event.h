#pragma once
#include "set_event.h"

namespace telimtmsd {

class SetRemoveEvent final : public SetEvent
{
public:
	SetRemoveEvent(
			Set* set,
			ObjSubject* subject,
			Item* oldItem) :
		SetEvent(set, subject),
		m_old(oldItem)
	{
	}

	auto oldItem() const { return m_old; }

private:
	Item* m_old;
};

template <typename T>
inline SetRemoveEvent const* toSetRemoveEvent(T event) { return static_cast<SetRemoveEvent const*>(event); }

}
