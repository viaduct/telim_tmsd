#include "item_type.h"

#include "manager.h"

namespace telimtmsd {

ItemType::ItemType(ItemRtti itemRtti) :
	m_itemRtti(itemRtti)
{
}

ItemRtti ItemType::itemRtti() const
{
	return m_itemRtti;
}

}
