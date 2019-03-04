#pragma once
#include <utility>
#include "item_type.h"
#include "value_alias.h"

namespace telimtmsd {

template <typename> class Value;

template <typename T>
class ValueType final : public ItemType
{
public:
	ValueType(ItemRtti itemRtti, T defaultValue);
	T const& defaultValue() const;

	Item* createItem(Manager* manager) const override;

private:
	T m_defaultValue;
};

}
