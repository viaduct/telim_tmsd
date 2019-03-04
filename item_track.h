#pragma once
#include "track.h"

namespace telimtmsd {

class Item;
class ItemSubject;
class ItemTrackInfo;
class ItemMimic;

class ItemTrack : public Track
{
public:
	ItemTrack(Track* parent);
	virtual ~ItemTrack();
	ItemTrack(ItemTrack const&) = delete;
	ItemTrack& operator =(ItemTrack const&) = delete;

	virtual ItemTrackInfo const* itemTrackInfo() const = 0;
	virtual Item* item() const = 0;

	virtual ItemMimic* getItemMimic(int key) = 0;
};

template <typename T>
inline ItemTrack* toItemTrack(T* one) { return static_cast<ItemTrack*>(one); }

}
