#pragma once
#include "member_id.h"

namespace telimtmsd {

class Obj;
class Cont;

/// ContType is an abstract type object for Cont.
///
/// All Cont instances have const reference of this.
class ContType
{
public:
	ContType(MemberId mid);
	ContType(ContType const&) = delete;
	ContType& operator =(ContType const&) = delete;

	/// Create Cont instance and add it to obj right away.
	virtual Cont* createCont(Obj* obj) const = 0;

	MemberId memberId() const;

private:
	MemberId m_mid;
};

}
