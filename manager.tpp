#pragma once
#include "manager.h"

namespace telimtmsd {

template <typename TType>
typename Chain<TType>::Data* Manager::create(const TType *type)
{
	auto const newItem = type->createItem(this);
	return static_cast<typename Chain<TType>::Data*>(newItem);
}

}
