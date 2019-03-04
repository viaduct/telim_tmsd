#pragma once
#include <functional>
#include <vector>
#include "cont.h"

namespace telimtmsd {

class ObjSubject;
class ListEvent;
class ListType;

class List final : public Cont
{
	using Items = std::vector<Item*>;
	using Iter = Items::iterator;
	using CIter = Items::const_iterator;

public:
	class PostAct;

	List(Obj* obj, ListType const* listType);
	virtual ~List();

	void stopRefer(Item* item, ContStopReferInfo** sri) override;
	void stopReferAll(ContStopReferInfo** sri) override;
	size_t referredItemsSize() const override;
	void referredItems(std::vector<Item*>* out) const override;
	ContTrack* createContTrack(
			ObjTrack* parent,
			ContTrackInfo const* trackInfo
			) override;

	ContType const* contType() const override;
	ListType const* listType() const;

	bool isEmpty() const;
	size_t size() const;
	void forItems(std::function<bool (Item*, size_t)> const& c) const;
//	void forItems_r(std::function<bool (Item*, size_t)> const& c) const;
//	void forMutItems(std::function<bool (Item*, size_t, PostAct*)> const& c);
//	void forMutItems_r(std::function<bool (Item*, size_t, PostAct*)> const& c);

	void append(ObjSubject* subject, Item* item);
	void insert(ObjSubject* subject, Item* item, size_t index);
	void move(ObjSubject* subject, size_t from, size_t howMany, size_t to);
	void remove(ObjSubject* subject, size_t from, size_t howMany);
	void clear(ObjSubject* subject);

private:
	Iter remove_intern(ObjSubject* subject, CIter iter, size_t index);

	Items m_items;
	ListType const* m_listType;
};

//class List::PostAct final
//{
//public:
//	enum : char
//	{
//		DoNothing,
//		DoRemove
//	};

//	char code() const;
//	ObjSubject* subject() const;
//	void remove(ObjSubject* subject);

//private:
//	ObjSubject* m_subject;
//	char m_code = DoNothing;
//};

template <typename T>
inline List* toList(T item) { return static_cast<List*>(item); }

}
