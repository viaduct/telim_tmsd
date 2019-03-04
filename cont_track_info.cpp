#include "cont_track_info.h"

#include "item_track_info.h"

namespace telimtmsd {

ContTrackInfo::ContTrackInfo(TrackId id, MemberId mid) :
	TrackInfo(id),
	m_mid(mid)
{
}

void ContTrackInfo::addItemTrackInfo(ItemRtti irtti, ItemTrackInfo *info)
{
	m_infos.emplace(irtti, info);
}

void ContTrackInfo::setDefaultItemTrackInfo(ItemTrackInfo *info)
{
	m_default = info;
}

const ItemTrackInfo*ContTrackInfo::itemTrackInfo(ItemRtti irtti) const
{
	auto const i = m_infos.find(irtti);
	if ( i != m_infos.end() )
	{
		return i->second;
	}
	else
	{
		return m_default;
	}
}

MemberId ContTrackInfo::memberId() const
{
	return m_mid;
}

}
