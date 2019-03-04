#include <cassert>

#include "item.h"

#include "item_event.h"

#include "item_subject.h"

#include "item_type.h"

#include "manager.h"

namespace telimtmsd {

Item::Item(Manager* manager) :
	m_manager(manager)
{
}

Manager*Item::manager() const
{
	return m_manager;
}

ItemRtti Item::itemRtti() const
{
	return itemType()->itemRtti();
}

void Item::emitExpire()
{
	ItemEvent e(this);
	e.setType(ItemEvent::Type::Expire_B);

	handleItemEvent(&e);
}

void Item::emitRefer(Item *referred)
{
	manager()->emitItemRefer(this, referred);
}

void Item::emitStopRefer(Item *referred)
{
	manager()->emitItemStopRefer(this, referred);
}

void Item::emitReferred(Item *referring)
{
	(void)referring;
}

void Item::emitStopReferred(Item *referring)
{
	(void)referring;
}

void Item::handleItemEvent(ItemEvent const* event)
{
	(void)event;
}

void *Item::gcPtr() const
{
	return m_gcPtr;
}

void Item::setGcPtr(void *one)
{
	m_gcPtr = one;
}

}
