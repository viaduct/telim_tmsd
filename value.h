#pragma once
#include <set>
#include <memory>
#include "item.h"
#include "value_alias.h"
#include "ptr_comp.h"

namespace telimtmsd {

template <typename T> class ValueSubject;
template <typename T> class ValueTrack;
template <typename T> class ValueType;

/// Value is a container for a lightweight copyable
/// type.
template <typename T>
class Value final : public Item
{
public:
	Value(
			Manager* manager,
			ValueType<T> const* valueType
			);
	virtual ~Value();

	void stopRefer(Item* item, StopReferInfo** sri) override;
	void stopReferAll(StopReferInfo** sri) override;
	size_t referredItemsSize() const override;
	std::vector<Item*> referredItems() const override;
	ItemTrack* createTrack(
			Track* parent,
			ItemTrackInfo const* trackInfo
			) override;
	ItemType const* itemType() const override;

	ValueType<T> const* valueType() const;

	/// Returns the current value.
	T const& get() const;
	/// @param subject subject which is calling this action.
	/// Can be nullptr.
	///
	/// Updates the current value.
	///
	/// Calling with subject will help you to remove event cycling,
	/// since the subject will be contained in event object.
	void set(ValueSubject<T>* subject, T t);

	ValueSubject<T>* createValueSubject();
	void freeValueSubject(ValueSubject<T>* subject);

protected:
	void handleItemEvent(ItemEvent const*) override;

private:
	void freeAllValueSubjects();

	std::set<std::unique_ptr<ValueSubject<T>>, PtrComp<ValueSubject<T>>> m_subjects;
	ValueType<T> const* m_valueType;
	T m_value{};
};

template <typename... Args, typename T>
inline Value<Args...>* toValue(T* one) { return static_cast<Value<Args...>*>(one); }

}
