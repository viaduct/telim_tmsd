#pragma once
#include "set_event.h"

namespace telimtmsd {

class SetClearEvent final : public SetEvent
{
public:
	SetClearEvent(
			Set* set,
			ObjSubject* subject
			) :
		SetEvent(set, subject)
	{
	}
};

template <typename T>
inline SetClearEvent const* toSetClearEvent(T event) { return static_cast<SetClearEvent const*>(event); }

}
