#pragma once
#include <functional>
#include <list>
#include "item_subject.h"

namespace telimtmsd {

template <typename T> class Value;
template <typename T> class ValueEvent;

template <typename T>
class ValueSubject final : public ItemSubject
{
public:
	ValueSubject(Value<T>* value) :
		m_value(value)
	{
	}

	Item* item() const override;

	Value<T>* value() const { return m_value; }
//	T const& get() const;
//	void set(T t) const;

	void freeThis() override;

	void emitEvent(ValueEvent<T> const* event);

	void listen(std::function<void (ValueEvent<T> const*)> callback);
	void stopListen();

private:
	std::function<void (ValueEvent<T> const*)> m_callback;
	Value<T>* m_value;
};

template <typename... Args, typename T>
inline ValueSubject<Args...>* toValueSubject(T* subject) { return static_cast<ValueSubject<Args...>*>(subject); }

}
