#include "bundle.h"
#include "no_matching_item_error.h"

#include "item.h"

namespace telimtmsd_comps {

void Bundle::setDefault(Item *item)
{
	m_default.reset(item);
}

void Bundle::add(Bundle::ItemRtti irtti, Item *item)
{
	m_items.emplace(irtti, item);
}

const Item *Bundle::matching(Bundle::ItemRtti irtti) const
{
	auto const iter = m_items.find(irtti);
	if ( iter != m_items.end() )
	{
		return iter->second.get();
	}
	else
	{
		if ( m_default )
		{
			return m_default.get();
		}
		else
		{
			throw NoMatchingItemError(this, irtti);
		}
	}
}

}
