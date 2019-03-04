#include "track_info.h"

namespace telimtmsd {

TrackInfo::TrackInfo(TrackId id) :
	m_id(id)
{
}

TrackId TrackInfo::trackId() const
{
	return m_id;
}

}
