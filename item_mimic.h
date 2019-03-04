#pragma once
#include "mimic.h"

namespace telimtmsd {

class ItemTrack;

class ItemMimic : public Mimic
{
public:
	using Mimic::Mimic;

	virtual ItemTrack* itemTrack() const = 0;
};

template <typename T>
inline ItemMimic* toItemMimic(T* one) { return static_cast<ItemMimic*>(one); }

}
