#pragma once
#include <functional>

namespace telimtmsd {

class Item;

class ItemSubject
{
public:
	ItemSubject() = default;
	virtual ~ItemSubject() = default;
	ItemSubject(ItemSubject const&) = delete;
	ItemSubject& operator =(ItemSubject const&) = delete;

	virtual Item* item() const = 0;
	virtual void freeThis() = 0;

	void emitExpired();
	void listenExpire(std::function<void ()> callback);
	void stopListenExpire();

private:
	std::function<void ()> m_subjectExpireCallback;
};

}
