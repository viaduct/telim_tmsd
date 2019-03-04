#include "single_stop_refer_info.h"

#include "single.h"

namespace telimtmsd {

void SingleStopReferInfo::stop() const
{
	if ( isTargetValid() )
	{
		single()->setNull(nullptr);
	}
}

void SingleStopReferInfo::rollback() const
{
	if ( isTargetValid() )
	{
		single()->setValid(nullptr, target());
	}
}

Single*SingleStopReferInfo::single() const
{
	return m_single;
}

bool SingleStopReferInfo::isTargetValid() const
{
	return m_target;
}

Item*SingleStopReferInfo::target() const
{
	return m_target;
}

void SingleStopReferInfo::setSingle(Single* one)
{
	m_single = one;
}

void SingleStopReferInfo::setTarget(Item* one)
{
	m_target = one;
}

}
