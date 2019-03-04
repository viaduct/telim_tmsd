#include "cont.h"

#include "cont_type.h"

namespace telimtmsd {

Cont::Cont(Obj* obj) :
	m_obj(obj)
{
}

MemberId Cont::memberId() const
{
	return contType()-> memberId();
}

Obj *Cont::obj() const
{
	return m_obj;
}

void Cont::listen(ObjSubject *subject, std::function<void (const ContEvent *)> callback)
{
	m_callbacks.emplace(subject, std::move(callback));
}

void Cont::stopListen(ObjSubject *subject)
{
	m_callbacks.erase(subject);
}

void Cont::stopListenAll()
{
	m_callbacks.clear();
}

void Cont::setDefaultItem(Item* item)
{
	(void)item;
}

void Cont::emitEvent(const ContEvent *event)
{
	for ( auto const& pair : m_callbacks )
	{
		pair.second(event);
	}
}

}
