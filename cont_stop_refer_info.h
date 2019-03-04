#pragma once

namespace telimtmsd {

class ContStopReferInfo
{
public:
	virtual ~ContStopReferInfo() = default;

	virtual void stop() const = 0;
	virtual void rollback() const = 0;
};

}
