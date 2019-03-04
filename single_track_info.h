#pragma once
#include "cont_track_info.h"

namespace telimtmsd {

class SingleTrackInfo final : public ContTrackInfo
{
public:
	using ContTrackInfo::ContTrackInfo;
};

template <typename T>
inline SingleTrackInfo const* toSingleTrackInfo(T const* info) { return static_cast<SingleTrackInfo const*>(info); }

}
