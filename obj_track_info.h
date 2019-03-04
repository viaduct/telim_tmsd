#pragma once
#include <functional>
#include <list>
#include <memory>
#include "item_track_info.h"
#include "member_id.h"
#include "cont_type.h"

namespace telimtmsd {

class ContTrackInfo;

class ObjTrackInfo final : public ItemTrackInfo
{
public:
	using ItemTrackInfo::ItemTrackInfo;

	void forContTrackInfos(std::function<bool (ContTrackInfo const*)> const& c) const;

	void addContTrackInfo(ContTrackInfo* info);

private:
	std::list<ContTrackInfo*> m_infos;
};

template <typename T>
inline ObjTrackInfo* toObjTrackInfo(T* info) { return static_cast<ObjTrackInfo*>(info); }
template <typename T>
inline ObjTrackInfo const* toObjTrackInfo(T const* info) { return static_cast<ObjTrackInfo const*>(info); }

}
