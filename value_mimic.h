#pragma once
#include "item_mimic.h"

namespace telimtmsd {

template <typename T> class Value;
template <typename T> class ValueTrack;
template <typename T> class ValueSubject;

template <typename T>
class ValueMimic : public ItemMimic
{
public:
	Track* track() const override final;
	ItemTrack* itemTrack() const override final;

	using ItemMimic::ItemMimic;

	void setValueTrack(ValueTrack<T>* one);

	ValueTrack<T>* valueTrack() const;
	ValueSubject<T>* valueSubject() const;
	Value<T>* value() const;
	T const& get() const;
	void set(T value) const;

	void emit_set_b(bool fromThis);
	void emit_set_a(bool fromThis);

protected:
	virtual void handle_set_b(bool fromThis);
	virtual void handle_set_a(bool fromThis);

private:
	ValueTrack<T>* m_track;
};

template <typename... Args, typename T>
inline ValueMimic<Args...>* toValueMimic(T* one) { return static_cast<ValueMimic<Args...>*>(one); }

}
