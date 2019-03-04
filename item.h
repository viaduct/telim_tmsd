#pragma once
#include <functional>
#include <map>
#include <utility>
#include <vector>
#include "cont_type.h"
#include "item_rtti.h"
#include "chain.h"

namespace telimtmsd {

class Manager;
class ItemEvent;
class ItemSubject;
class ItemTrack;
class ItemTrackInfo;
class Track;
class ItemType;
class StopReferInfo;

/// Item is an abstract type which holds data.
///
/// By itself, it contains no data at all, and that's
/// subclasses' job.
///
/// It introduces abstract data-modifying functions
/// such as stopRefer() and stopReferAll(). These functions
/// returns informations for what they actually have done,
/// so that the jobs can be undone.
///
/// An Item instance can be expired, means being deleted
/// in most cases, by Manager. Manager will call emitExpired()
/// before it becomes inaccessable, and before it returns
/// handleItemEvent() with Expire_B event type will be called.
class Item
{
public:
	Item(Manager* manager);

	Manager* manager() const;

	/// @param item stop referring target
	/// @param sri command object which has detailed information output
	///
	/// Returns a command object which can stop referring
	/// given item. sri need to be deleted manually.
	virtual void stopRefer(Item* item, StopReferInfo** sri) = 0;
	/// @param sri detailed information output
	///
	/// Returns a command object which can stop referring
	/// all items. sri need to be deleted manually.
	virtual void stopReferAll(StopReferInfo** sri) = 0;
	virtual size_t referredItemsSize() const = 0;
	virtual std::vector<Item*> referredItems() const = 0;
	/// @param parent parent Track instance which will be given as
	/// constructor parameter.
	/// @param trackInfo TrackInfo instance which will be given as
	/// constructor parameter.
	///
	/// Creates ItemTrack subclass of matching type.
	virtual ItemTrack* createTrack(
			Track* parent,
			ItemTrackInfo const* trackInfo
			) = 0;
	/// Returns ItemType instance.
	///
	/// Return value must not be changed after an Item instance is
	/// constructed.
	virtual ItemType const* itemType() const = 0;

	/// Returns ItemRtti value.
	///
	/// Return value must not be changed after an Item instance is
	/// constructed.
	ItemRtti itemRtti() const;

	/// Emits ItemEvent with ItemEvent::Type::Expire_B type.
	///
	/// handleItemEvent() will be called with above event.
	///
	/// This is intended to be called from Manager, only.
	void emitExpire();

protected:
	/// Let the library knows that the subclass started
	/// to refer another item.
	///
	/// This must be called when Item's subclass
	/// takes reference fo other Item instances.
	///
	/// This can be called multiple times for the same
	/// instances. If it happens, emitStopRefer() need to
	/// be called the same number of times as well, when
	/// stop referring.
	void emitRefer(Item* referred);
	/// Let the library knows that the subclass started
	/// to refer another item.
	///
	/// @see emitRefer()
	void emitStopRefer(Item* referred);
	/// This is intended to be called from Item itself,
	/// not from its subclasses. Do not call this function
	/// unless you know what you are actually doing.
	void emitReferred(Item* referring);
	/// This is intended to be called from Item itself,
	/// not from its subclasses. Do not call this function
	/// unless you know what you are actually doing.
	void emitStopReferred(Item* referring);

	/// This is called when Item wants to propagate
	/// ItemEvent to its subclasses.
	///
	/// ItemEvent::Type::Expire_B will be called right before
	/// an Item instance is invalidated.
	virtual void handleItemEvent(ItemEvent const*);

	void* gcPtr() const;
	void setGcPtr(void* one);

private:
	Manager* m_manager;
	void* m_gcPtr;
};

}
