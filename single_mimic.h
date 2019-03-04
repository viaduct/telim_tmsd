#pragma once
#include "cont_mimic.h"

namespace telimtmsd {

class Single;
class SingleTrack;

class SingleMimic : public ContMimic
{
public:
	Track* track() const override final;
	ContTrack* contTrack() const override final;

	bool isUniqueChildValid() const override;
	ItemMimic* uniqueChild() override;

	using ContMimic::ContMimic;

	void setSingleTrack(SingleTrack* one);

	SingleTrack* singleTrack() const;
	Single* single() const;

	template <typename T> typename Chain<T>::Mimic* itemMimic() const
	{
		return static_cast<typename Chain<T>::Mimic*>(itemMimic());
	}
	bool isItemMimicValid() const;
	ItemMimic* itemMimic() const;

	template <typename T> typename Chain<T>::Mimic* child() const
	{
		return static_cast<typename Chain<T>::Mimic*>(child());
	}
	bool isChildValid() const;
	ItemMimic* child() const;

	void emit_validSet_b(bool fromThis);
	void emit_validSet_a(bool fromThis);
	void emit_nullSet_b(bool fromThis);
	void emit_nullSet_a(bool fromThis);

protected:
	virtual void handle_validSet_b(bool fromThis);
	virtual void handle_validSet_a(bool fromThis);
	virtual void handle_nullSet_b(bool fromThis);
	virtual void handle_nullSet_a(bool fromThis);

private:
	SingleTrack* m_track;
};

template <typename T>
inline SingleMimic* toSingleMimic(T* one) { return static_cast<SingleMimic*>(one); }

}
