#pragma once
#include "cont_track_info.h"

namespace telimtmsd {

class ListTrackInfo final : public ContTrackInfo
{
public:
	using ContTrackInfo::ContTrackInfo;
};

template <typename T>
inline ListTrackInfo const* toListTrackInfo(T const* info) { return static_cast<ListTrackInfo const*>(info); }

}
