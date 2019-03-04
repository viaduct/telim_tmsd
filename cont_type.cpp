#include "cont_type.h"

namespace telimtmsd {

ContType::ContType(MemberId mid) :
	m_mid(mid)
{
}

MemberId ContType::memberId() const
{
	return m_mid;
}

}
