#pragma once
#include <memory>
#include <map>
#include "item_rtti.h"
#include "track_info.h"
#include "member_id.h"

namespace telimtmsd {

class ItemTrackInfo;
class ObjTrack;
class ContTrack;

class ContTrackInfo : public TrackInfo
{
public:
	ContTrackInfo(TrackId id, MemberId mid);

	void addItemTrackInfo(ItemRtti irtti, ItemTrackInfo* info);
	void setDefaultItemTrackInfo(ItemTrackInfo* info);

	ItemTrackInfo const* itemTrackInfo(ItemRtti irtti) const;
	MemberId memberId() const;

private:
	std::map<ItemRtti, ItemTrackInfo*> m_infos;
	ItemTrackInfo* m_default;
	MemberId m_mid;
};

template <typename T>
inline ContTrackInfo const* toContTrackInfo(T const* one) { return static_cast<ContTrackInfo const*>(one); }

}
