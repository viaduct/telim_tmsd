#pragma once

namespace telimtmsd {

class StopReferInfo
{
public:
	virtual ~StopReferInfo() = default;

	virtual void stop() const = 0;
	virtual void rollback() const = 0;
};

}
