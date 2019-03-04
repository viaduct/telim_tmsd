#pragma once
#include "cont_type.h"

namespace telimtmsd {

class ListType final : public ContType
{
public:
	using ContType::ContType;

	Cont* createCont(Obj* obj) const override;
};

}
