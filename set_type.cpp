#include "set_type.h"

#include "set.h"

#include "obj.h"

namespace telimtmsd {

Cont*SetType::createCont(Obj* obj) const
{
	auto const newCont = new Set(obj, this);
	obj->addCont(newCont);
	return newCont;
}

}
