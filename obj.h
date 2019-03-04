#pragma once
#include <memory>
#include <map>
#include <set>
#include "item.h"
#include "member_id.h"
#include "ptr_comp.h"

namespace telimtmsd {

class SingleEvent;
class Cont;
class Single;
class Set;
class List;
class ObjSubject;
class ObjType;

class Obj final : public Item
{
public:
	Obj(
			Manager* manager,
			ObjType const* objType
			);
	virtual ~Obj();

	void stopRefer(Item* item, StopReferInfo** sri) override;
	void stopReferAll(StopReferInfo** sri) override;
	size_t referredItemsSize() const override;
	std::vector<Item*> referredItems() const override;
	ItemTrack* createTrack(
			Track* parent,
			ItemTrackInfo const* trackInfo
			) override;

	ItemType const* itemType() const override;
	ObjType const* objType() const;

	void addCont(Cont* cont);
	bool has(MemberId id) const;
	Cont* cont(MemberId id);
	template <typename T> typename Chain<T>::Data* cont(MemberId id)
	{
		return static_cast<typename Chain<T>::Data*>(cont(id));
	}

	ObjSubject* createObjSubject();
	void freeObjSubject(ObjSubject* subject);
	void freeAllObjSubjects();

	// So that they can be used from Cont.
	using Item::emitRefer;
	using Item::emitStopRefer;

protected:
	void handleItemEvent(const ItemEvent * event) override;

private:
	std::set<std::unique_ptr<ObjSubject>, PtrComp<ObjSubject>> m_subjects;
	std::map<MemberId, std::unique_ptr<Cont>> m_conts;
	ObjType const* m_objType;
};

template <typename T>
inline Obj* toObj(T item) { return static_cast<Obj*>(item); }

}
