#pragma once
#include "track_info.h"

namespace telimtmsd {

class Track;
class ItemTrack;

class ItemTrackInfo : public TrackInfo
{
public:
	using TrackInfo::TrackInfo;
};

template <typename T>
inline ItemTrackInfo* toItemTrackInfo(T* one) { return static_cast<ItemTrackInfo*>(one); }
template <typename T>
inline ItemTrackInfo const* toItemTrackInfo(T const* one) { return static_cast<ItemTrackInfo const*>(one); }

}
