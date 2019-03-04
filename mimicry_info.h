#pragma once

namespace telimtmsd {

class Mimic;
class TrackInfo;

class MimicryInfo
{
public:
	MimicryInfo() = default;
	virtual ~MimicryInfo() = default;
	MimicryInfo(MimicryInfo const&) = delete;
	MimicryInfo& operator =(MimicryInfo const&) = delete;

	virtual Mimic* createMimic(TrackInfo const*) = 0;
};

}
