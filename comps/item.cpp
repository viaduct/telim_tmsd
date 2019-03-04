#include "item.h"

#include "bundle.h"

namespace telimtmsd_comps {

Item::Pack::Pack(
		MemberId mid,
		ContType contType,
		Bundle* bundle
		) :
	bundle(bundle),
	mid(mid),
	contType(contType)
{
}

Item::Pack::~Pack() = default;

}
