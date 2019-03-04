#include "list_type.h"

#include "list.h"

#include "obj.h"

namespace telimtmsd {

Cont*ListType::createCont(Obj* obj) const
{
	auto const newCont = new List(obj, this);
	obj->addCont(newCont);
	return newCont;
}

}
