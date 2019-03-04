#include "list_stop_refer_info.h"

#include "list.h"

namespace telimtmsd {

void ListStopReferInfo::stop() const
{
	auto c = [this](Item* item, size_t index)->bool
	{
		(void)item;
		list()->remove(nullptr, index, 1);
		return true;
	};
	forTargetsFromEnd(std::cref(c));
}

void ListStopReferInfo::rollback() const
{
	auto c = [this](Item* item, size_t index)->bool
	{
		list()->insert(nullptr, item, index);
		return true;
	};
	forTargetsFromBegin(std::cref(c));
}

List*ListStopReferInfo::list() const
{
	return m_list;
}

size_t ListStopReferInfo::targetsSize() const
{
	return m_targets.size();
}

void ListStopReferInfo::forTargetsFromBegin(std::function<bool (Item*, size_t)> c) const
{
	bool resume = true;
	for ( auto i = m_targets.begin(); resume && i != m_targets.end(); ++i )
	{
		resume = c((*i).item, (*i).index);
	}
}

void ListStopReferInfo::forTargetsFromEnd(std::function<bool (Item*, size_t)> c) const
{
	bool resume = true;
	for ( auto i = m_targets.rbegin(); resume && i != m_targets.rend(); ++i )
	{
		resume = c((*i).item, (*i).index);
	}
}

void ListStopReferInfo::setList(List* one)
{
	m_list = one;
}

void ListStopReferInfo::reserve(size_t size)
{
	m_targets.reserve(size);
}

void ListStopReferInfo::add(Item* target, size_t index)
{
	m_targets.push_back(Target{target, index});
}

}
