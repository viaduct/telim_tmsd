#pragma once
#include "chain.h"

namespace telimtmsd {

class Track;

class Mimic
{
public:
	Mimic() = default;
	virtual ~Mimic() = default;
	Mimic(Mimic const&) = delete;
	Mimic& operator =(Mimic const&) = delete;

	virtual Track* track() const = 0;
	Mimic* parent() const;

	int key() const;
	void setKey(int one);

	void* userPtr() const;
	void setUserPtr(void* ptr);

	template <typename T> T* userPtr() const;
	template <typename T, typename Given> void setUserPtr(Given given);

private:
	void* m_userPtr;
	int m_key;
};

template <typename T>
T* Mimic::userPtr() const
{
	return static_cast<T*>(m_userPtr);
}
template <typename T, typename Given>
void Mimic::setUserPtr(Given given)
{
	m_userPtr = static_cast<T*>(given);
}

}
