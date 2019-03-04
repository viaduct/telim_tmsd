#include <cstdio>

#include "no_matching_item_error.h"

#include "bundle.h"

namespace telimtmsd_comps {

NoMatchingItemError::NoMatchingItemError(const Bundle *bundle, ItemRtti irtti) noexcept :
	m_bundle(bundle), m_itemRtti(irtti)
{
	size_t count = 0;

#define handle_rc_\
	if ( rc >= 0 )\
	{\
		count += rc;\
	}\
	else\
	{\
		return;\
	}

	int rc;
	rc = snprintf(
				m_data + count,
				sizeof(m_data) - count,
				"No matching ItemRtti, can accpet "
				);
	handle_rc_

	bool runAtLeastOnce = false;
	m_bundle->forItems([this, &count, &runAtLeastOnce](auto irtti, auto)
	{
		int rc = snprintf(
					m_data + count,
					sizeof(m_data) - count,
					"%d, ",
					(int)irtti
					);
		handle_rc_
		runAtLeastOnce = true;
	});
	// Remove suffix comma.
	if ( runAtLeastOnce )
	{
		count -= 2;
		m_data[count] = 0;
	}

	rc = snprintf(
				m_data + count,
				sizeof(m_data) - count,
				" but %d given.",
				(int)m_itemRtti
				);
	handle_rc_
}

}
