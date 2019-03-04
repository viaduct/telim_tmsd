#include "set_stop_refer_info.h"

#include "set.h"

namespace telimtmsd {

void SetStopReferInfo::stop() const
{
	for ( Item* target : m_targets )
	{
		set()->remove(nullptr, target);
	}
}

void SetStopReferInfo::rollback() const
{
	for ( Item* target : m_targets )
	{
		set()->add(nullptr, target);
	}
}

Set*SetStopReferInfo::set() const
{
	return m_set;
}

size_t SetStopReferInfo::targetsSize() const
{
	return m_targets.size();
}

void SetStopReferInfo::forTargets(std::function<bool (Item*)> c) const
{
	bool resume = true;
	for ( auto i = m_targets.begin(); resume && i != m_targets.end(); ++i )
	{
		resume = c(*i);
	}
}

void SetStopReferInfo::setSet(Set* one)
{
	m_set = one;
}

void SetStopReferInfo::reserve(size_t size)
{
	m_targets.reserve(size);
}

void SetStopReferInfo::add(Item* target)
{
	m_targets.push_back(target);
}

}
