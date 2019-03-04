#include "manager.tpp"

#include "item.h"

#include "item_type.h"

namespace telimtmsd {

namespace {
NullGcObserver nullGcObs_;
}
NullGcObserver *GcObserver::null()
{
	return &nullGcObs_;
}

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::addItem(Item *item)
{
	m_items.emplace(item);

	m_gcObs->handleItemAdd(item);
}

void Manager::destroy(Item *item)
{
	m_gcObs->handleItemRemove(item);

	item->emitExpire();
	auto const i = m_items.find(item);
	m_items.erase(i);
}

void Manager::emitItemRefer(Item *referring, Item *referred)
{
	m_gcObs->handleItemRefer(referring, referred);
}

void Manager::emitItemStopRefer(Item *referring, Item *referred)
{
	m_gcObs->handleItemStopRefer(referring, referred);
}

void Manager::setGcObserver(GcObserver *obs)
{
	m_gcObs = obs;
}

}
