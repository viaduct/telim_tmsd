#pragma once
#include <set>
#include <memory>
#include "ptr_comp.h"
#include "chain.h"

namespace telimtmsd {

class Item;
class ItemType;

class NullGcObserver;

class GcObserver
{
public:
	virtual ~GcObserver() = default;

	virtual void handleItemAdd(Item* item) = 0;
	virtual void handleItemRemove(Item* item) = 0;
	virtual void handleItemRefer(Item* referring, Item* referred) = 0;
	virtual void handleItemStopRefer(Item* referring, Item* referred) = 0;

	static NullGcObserver* null();
};

class NullGcObserver final : public GcObserver
{
public:
	void handleItemAdd(Item*) override {}
	void handleItemRemove(Item*) override {}
	void handleItemRefer(Item*, Item*) override {}
	void handleItemStopRefer(Item*, Item*) override {}
};

class Manager final
{
public:
	Manager();
	~Manager();
	Manager(Manager const&) = delete;
	Manager& operator =(Manager const&) = delete;

	template <typename TType>
	typename Chain<TType>::Data* create(TType const* type);
	void destroy(Item* item);

	/// Intended to be called from ItemType or its subclasses.
	void addItem(Item* item);

	/// Intended to be called from Item::emitStopRefer().
	void emitItemRefer(Item* referring, Item* referred);
	/// Intended to be called from Item::emitRefer().
	void emitItemStopRefer(Item* referring, Item* referred);

	void setGcObserver(GcObserver* obs);

private:
	std::set<std::unique_ptr<Item>, PtrComp<Item>> m_items;
	GcObserver* m_gcObs = GcObserver::null();
};

}
