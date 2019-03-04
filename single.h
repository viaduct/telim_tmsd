#pragma once
#include <set>
#include <memory>
#include "cont.h"

namespace telimtmsd {

class ObjSubject;
class SingleEvent;
class SingleType;

class Single final : public Cont
{
public:
	Single(Obj* obj, SingleType const* singleType);
	virtual ~Single();

	void stopRefer(Item* item, ContStopReferInfo** sri) override;
	void stopReferAll(ContStopReferInfo** sri) override;

	ContTrack* createContTrack(
			ObjTrack* parent,
			ContTrackInfo const* trackInfo
			) override;
	size_t referredItemsSize() const override;
	void referredItems(std::vector<Item*>* out) const override;
	ContType const* contType() const override;
	SingleType const* singleType() const;

	void setDefaultItem(Item* item) override;

	template <typename T> typename Chain<T>::Data* get() const
	{
		return static_cast<typename Chain<T>::Data*>(get());
	}
	bool isValid() const;
	Item* get() const;

	void setValid(ObjSubject* subject, Item* one);
	void setNull(ObjSubject* subject);

private:
	SingleType const* m_singleType;
	Item* m_item = nullptr;
};

template <typename T>
inline Single* toSingle(T item) { return static_cast<Single*>(item); }

}
