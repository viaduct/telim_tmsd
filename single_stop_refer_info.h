#pragma once
#include "cont_stop_refer_info.h"

namespace telimtmsd {

class Single;
class Item;

class SingleStopReferInfo final : public ContStopReferInfo
{
public:
	void stop() const override;
	void rollback() const override;

	Single* single() const;
	bool isTargetValid() const;
	Item* target() const;

	void setSingle(Single* one);
	void setTarget(Item* one);

private:
	Single* m_single;
	Item* m_target = nullptr;
};

}
