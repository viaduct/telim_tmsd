#pragma once
#include "cont_track_info.h"

namespace telimtmsd {

class SetTrackInfo final : public ContTrackInfo
{
public:
	using ContTrackInfo::ContTrackInfo;
};

template <typename T>
inline SetTrackInfo const* toSetTrackInfo(T const* info) { return static_cast<SetTrackInfo const*>(info); }

}
