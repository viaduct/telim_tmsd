#pragma once
#include <vector>
#include <functional>
#include "item_mimic.h"
#include "member_id.h"

namespace telimtmsd {

class Obj;
class ObjTrack;
class ContMimic;

class ObjMimic : public ItemMimic
{
public:
	Track* track() const override final;
	ItemTrack* itemTrack() const override final;

	using ItemMimic::ItemMimic;

	void setObjTrack(ObjTrack* one);

	ObjTrack* objTrack() const;
	Obj* obj() const;

	template <typename T>
	typename Chain<T>::Mimic* contMimic(MemberId mid) const
	{
		return static_cast<typename Chain<T>::Mimic*>(contMimic(mid));
	}
	template <typename T>
	typename Chain<T>::Mimic* contMimic_safe(MemberId mid) const
	{
		return static_cast<typename Chain<T>::Mimic*>(contMimic_safe(mid));
	}
	ContMimic* contMimic(MemberId mid) const;
	ContMimic* contMimic_safe(MemberId mid) const;
	bool hasContMimic(MemberId mid) const;
	void forContMimics(std::function<bool (MemberId, ContMimic*)> const& c) const;
	std::vector<std::tuple<MemberId, ContMimic*>> contMimics() const;
	size_t contMimicsSize() const;

	// With different name.
	template <typename T>
	typename Chain<T>::Mimic* child(MemberId mid) const
	{
		return static_cast<typename Chain<T>::Mimic*>(child(mid));
	}
	template <typename T>
	typename Chain<T>::Mimic* child_safe(MemberId mid) const
	{
		return static_cast<typename Chain<T>::Mimic*>(child_safe(mid));
	}
	ContMimic* child(MemberId mid) const;
	ContMimic* child_safe(MemberId mid) const;
	bool hasChild(MemberId mid) const;
	std::vector<std::tuple<MemberId, ContMimic*>> children() const;
	size_t childrenSize() const;

private:
	ObjTrack* m_track;
};

template <typename T>
inline ObjMimic* toObjMimic(T* one) { return static_cast<ObjMimic*>(one); }

}
