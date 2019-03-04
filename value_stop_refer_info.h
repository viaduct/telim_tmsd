#pragma once
#include "stop_refer_info.h"

namespace telimtmsd {

class ValueStopReferInfo final : public StopReferInfo
{
public:
	void stop() const override;
	void rollback() const override;
};

}
