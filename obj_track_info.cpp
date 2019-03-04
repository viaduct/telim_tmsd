#include "obj_track_info.h"

#include "cont_track_info.h"

namespace telimtmsd {

void ObjTrackInfo::addContTrackInfo(ContTrackInfo* info)
{
	m_infos.emplace_back(info);
}

void ObjTrackInfo::forContTrackInfos(const std::function<bool (const ContTrackInfo*)>& c) const
{
	bool resume = true;
	for ( auto i = m_infos.begin(); resume && i != m_infos.end(); ++i )
	{
		resume = c((*i));
	}
}

}
