#include "single_type.h"

#include "single.h"

#include "obj.h"

namespace telimtmsd {

Cont*SingleType::createCont(Obj* obj) const
{
	auto const newCont = new Single(obj, this);
	obj->addCont(newCont);
	return newCont;
}

}
