#include <cassert>

#include "obj_type.h"
#include "obj.h"

#include "single.h"

#include "manager.h"

namespace telimtmsd {

Item *ObjType::createItem(Manager* manager) const
{
	auto const newObj = new Obj(manager, this);
	manager->addItem(newObj);

	{
		auto l = [newObj, manager](
				ContType const* contType,
				ItemType const* defaultItemType
				)->bool
		{
			auto const newCont = contType->createCont(newObj);
			if ( defaultItemType )
			{
				auto const defaultItem = defaultItemType->createItem(manager);
				newCont->setDefaultItem(defaultItem);
			}
			return true;
		};
		forContTypes(std::cref(l));
	}

	return newObj;
}

void ObjType::forContTypes(std::function<bool (ContType const*, ItemType const*)> const& c) const
{
	bool resume = true;
	for ( auto i = m_contTypes.begin(); resume && i != m_contTypes.end(); ++i )
	{
		resume = c((*i).contType, (*i).defaultItemType);
	}
}

void ObjType::addContType(
		ContType const* contType,
		ItemType const* defaultItemType
		)
{
	m_contTypes.push_back(Pack{contType, defaultItemType});
}

}
