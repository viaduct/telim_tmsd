#pragma once
#include <functional>
#include <vector>
#include "cont_stop_refer_info.h"

namespace telimtmsd {

class Set;
class Item;

class SetStopReferInfo final : public ContStopReferInfo
{
public:
	void stop() const override;
	void rollback() const override;

	Set* set() const;
	size_t targetsSize() const;
	void forTargets(std::function<bool (Item*)> c) const;

	void setSet(Set* one);
	void reserve(size_t size);
	void add(Item* target);

private:
	std::vector<Item*> m_targets;
	Set* m_set;
};

}
