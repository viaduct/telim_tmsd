#pragma once
#include "value_type.h"
#include "value.h"

#include "manager.h"

namespace telimtmsd {

template<typename T>
ValueType<T>::ValueType(ItemRtti itemRtti, T defaultValue) :
	ItemType(itemRtti),
	m_defaultValue(std::move(defaultValue))
{
}

template<typename T>
T const& ValueType<T>::defaultValue() const
{
	return m_defaultValue;
}

template<typename T>
Item *ValueType<T>::createItem(Manager* manager) const
{
	auto const newValue = new Value<T>(manager, this);
	manager->addItem(newValue);

	newValue->set(nullptr, m_defaultValue);

	return newValue;
}

}
