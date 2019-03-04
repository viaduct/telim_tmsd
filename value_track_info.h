#pragma once
#include "item_track_info.h"

namespace telimtmsd {

template <typename T>
class ValueTrackInfo final : public ItemTrackInfo
{
public:
	using ItemTrackInfo::ItemTrackInfo;
};

template <typename... Args, typename T>
inline ValueTrackInfo<Args...>* toValueTrackInfo(T* info) { return static_cast<ValueTrackInfo<Args...>*>(info); }
template <typename... Args, typename T>
inline ValueTrackInfo<Args...> const* toValueTrackInfo(T const* info) { return static_cast<ValueTrackInfo<Args...> const*>(info); }

}
