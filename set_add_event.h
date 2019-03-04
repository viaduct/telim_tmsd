#pragma once
#include "set_event.h"

namespace telimtmsd {

class SetAddEvent final : public SetEvent
{
public:
	SetAddEvent(
			Set* set,
			ObjSubject* subject,
			Item* newItem
			) :
		SetEvent(set, subject),
		m_new(newItem)
	{
	}

	auto newItem() const { return m_new; }

private:
	Item* m_new;
};

template <typename T>
inline SetAddEvent const* toSetAddEvent(T event) { return static_cast<SetAddEvent const*>(event); }

}
