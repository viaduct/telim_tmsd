#pragma once
#include "cont_type.h"
#include "item_rtti.h"

namespace telimtmsd {

class Item;
class Manager;

/// ItemType is an abstract type object for Item.
///
/// All Item instances have const reference of this.
class ItemType
{
public:
	ItemType(ItemRtti itemRtti);
	ItemRtti itemRtti() const;

	/// Create an Item instance and add it to Manager
	/// right away.
	virtual Item* createItem(Manager* manager) const = 0;

private:
	ItemRtti m_itemRtti;
};

}
