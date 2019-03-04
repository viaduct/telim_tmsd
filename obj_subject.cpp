#include "obj_subject.h"

#include "obj.h"

#include "single.h"
#include "set.h"
#include "list.h"

namespace telimtmsd {

ObjSubject::ObjSubject(Obj *obj) :
	m_obj(obj)
{
}

Item *ObjSubject::item() const { return m_obj; }

void ObjSubject::listenCont(MemberId id, std::function<void (const ContEvent *)> callback)
{
	m_obj->cont(id)->listen(this, std::move(callback));
}

void ObjSubject::stopListen(MemberId id)
{
	m_obj->cont(id)->stopListen(this);
}

void ObjSubject::freeThis()
{
	m_obj->freeObjSubject(this);
}

}
