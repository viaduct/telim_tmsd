#pragma once
#include <list>
#include <memory>
#include <functional>
#include "item_type.h"

namespace telimtmsd {

class Obj;

class ObjType final : public ItemType
{
public:
	using ItemType::ItemType;

	Item* createItem(Manager* manager) const override;
	void forContTypes(std::function<bool (ContType const*, ItemType const*)> const& c) const;
	void addContType(
			ContType const* contType,
			ItemType const* defaultItemType = nullptr
			);

private:
	struct Pack final
	{
		ContType const* contType;
		ItemType const* defaultItemType;
	};
	std::list<Pack> m_contTypes;
};

}
