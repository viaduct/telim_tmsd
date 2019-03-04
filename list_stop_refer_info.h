#pragma once
#include <functional>
#include <vector>
#include "cont_stop_refer_info.h"

namespace telimtmsd {

class List;
class Item;

class ListStopReferInfo final : public ContStopReferInfo
{
public:
	void stop() const override;
	void rollback() const override;

	List* list() const;
	size_t targetsSize() const;
	void forTargetsFromBegin(std::function<bool (Item*, size_t)> c) const;
	void forTargetsFromEnd(std::function<bool (Item*, size_t)> c) const;

	void setList(List* one);
	void reserve(size_t size);
	void add(Item* target, size_t index);

private:
	struct Target final
	{
		Item* item;
		size_t index;
	};
	std::vector<Target> m_targets;
	List* m_list;
};

}
