#pragma once
#include "track_id.h"

namespace telimtmsd {

class TrackInfo
{
public:
	TrackInfo(TrackId id);
	TrackInfo(TrackInfo const&) = delete;
	TrackInfo& operator =(TrackInfo const&) = delete;

	TrackId trackId() const;

private:
	TrackId m_id;
};

}
