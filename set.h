#pragma once
#include <set>
#include <functional>
#include "cont.h"

namespace telimtmsd {

class ObjSubject;
class SetEvent;
class SetType;

class Set final : public Cont
{
	using Items = std::set<Item*>;
	using Iter = Items::iterator;
	using CIter = Items::const_iterator;

public:
	class PostAct;

	Set(Obj* obj, SetType const* setType);
	virtual ~Set();

	void stopRefer(Item* item, ContStopReferInfo** sri) override;
	void stopReferAll(ContStopReferInfo** sri) override;
	size_t referredItemsSize() const override;
	void referredItems(std::vector<Item*>* out) const override;
	ContTrack* createContTrack(
			ObjTrack* parent,
			ContTrackInfo const* trackInfo
			) override;

	ContType const* contType() const override;
	SetType const* setType() const;

	bool isEmpty() const;
	size_t size() const;
	void forItems(std::function<bool (Item*)> const& c) const;
//	template <typename C> void forItems(C const& c) const;
//	template <typename C> void forMutItems(C const& c);

	bool add(ObjSubject* subject, Item* item);
	bool remove(ObjSubject* subject, Item* item);
	void clear(ObjSubject* subject);

private:
	std::pair<Iter, bool> add_intern(ObjSubject* subject, Item* item);
	bool remove_intern(ObjSubject* subject, Item* item);
	Iter remove_intern(ObjSubject* subject, CIter iter);

	std::set<Item*> m_items;
	SetType const* m_setType;
};

//class Set::PostAct final
//{
//public:
//	enum : char
//	{
//		DoNothing,
//		DoRemove
//	};

//	char code() const { return m_code; }
//	ObjSubject* subject() const { return m_subject; }
//	void remove(ObjSubject* subject)
//	{
//		m_subject = subject;
//		m_code = DoRemove;
//	}

//private:
//	ObjSubject* m_subject;
//	char m_code = DoNothing;
//};

//template <typename C> void Set::forMutItems(C const& c)
//{
//	for ( auto iter = m_items.begin(); iter != m_items.end(); ++iter )
//	{
//		PostAct act;
//		c(*iter, &act);

//		switch ( act.code() )
//		{
//			case PostAct::DoRemove:
//				iter = remove_intern(act.subject(), iter);
//				break;
//			default:
//				break;
//		}
//	}
//}

//template <typename C> void Set::forItems(C const& c) const
//{
//	for ( auto iter = m_items.begin(); iter != m_items.end(); ++iter )
//	{
//		c(*iter);
//	}
//}

template <typename T>
inline Set* toSet(T item) { return static_cast<Set*>(item); }

}
