#pragma once
#include <map>
#include <memory>
#include "item_rtti.h"

namespace telimtmsd_comps {

namespace tmsd = telimtmsd;

class Item;

class Bundle final
{
public:
	using ItemRtti = tmsd::ItemRtti;

	void setDefault(Item* item);
	void add(ItemRtti irtti, Item* item);

	template <typename C> void forItems(C const& c) const;
	Item const* matching(ItemRtti irtti) const;
	bool has(ItemRtti irtti) const
	{
		return m_items.find(irtti) != m_items.end();
	}

private:
	std::map<ItemRtti, std::unique_ptr<Item>> m_items;
	std::unique_ptr<Item> m_default;
};

template <typename C> void Bundle::forItems(C const& c) const
{
	for ( auto const& pair : m_items )
	{
		c(pair.first, const_cast<Item const*>(pair.second.get()));
	}
}

}
