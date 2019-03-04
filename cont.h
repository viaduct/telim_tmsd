#pragma once
#include <map>
#include <functional>
#include <vector>
#include "member_id.h"
#include "chain.h"

namespace telimtmsd {

class Item;
class Obj;
class ObjSubject;
class ContEvent;
class ContStopReferInfo;
class ObjTrack;
class ContTrack;
class ContTrackInfo;
class ContType;

class Cont
{
public:
	Cont(Obj* obj);
	virtual ~Cont() = default;
	Cont(Cont const&) = delete;
	Cont& operator =(Cont const&) = delete;

	virtual void stopRefer(Item* item, ContStopReferInfo** sri) = 0;
	virtual void stopReferAll(ContStopReferInfo** sri) = 0;
	virtual size_t referredItemsSize() const = 0;
	virtual void referredItems(std::vector<Item*>* out) const = 0;
	virtual ContTrack* createContTrack(
			ObjTrack* parent,
			ContTrackInfo const* trackInfo
			) = 0;

	virtual ContType const* contType() const = 0;
	MemberId memberId() const;
	Obj* obj() const;

	void listen(ObjSubject* subject, std::function<void (ContEvent const*)> callback);
	void stopListen(ObjSubject* subject);
	void stopListenAll();

	virtual void setDefaultItem(Item* item);

protected:
	void emitEvent(ContEvent const* event);

private:
	std::map<ObjSubject*, std::function<void (ContEvent const*)>> m_callbacks;
	Obj* m_obj;
};

}
