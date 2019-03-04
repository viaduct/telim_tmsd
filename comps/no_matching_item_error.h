#pragma once
#include <exception>
#include "item_rtti.h"

namespace telimtmsd_comps {

class Bundle;

namespace tmsd = telimtmsd;

class NoMatchingItemError final : public std::exception
{
public:
	using ItemRtti = tmsd::ItemRtti;

	NoMatchingItemError(Bundle const* bundle, ItemRtti irtti) noexcept;
	char const* what() const noexcept override
	{
		return m_data;
	}

	Bundle const* bundle() const noexcept { return m_bundle; }
	ItemRtti given() const noexcept { return m_itemRtti; }

private:
	char m_data[200];
	Bundle const* m_bundle;
	ItemRtti m_itemRtti;
};

}
