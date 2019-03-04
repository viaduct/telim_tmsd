#include "obj.h"

#include "single.h"
#include "set.h"
#include "list.h"

#include "obj_subject.h"

#include "obj_track.h"

#include "obj_track_info.h"

#include "obj_type.h"

#include "obj_stop_refer_info.h"

#include "item_event.h"

namespace telimtmsd {

Obj::Obj(
		Manager* manager,
		ObjType const* objType
		) :
	Item(manager),
	m_objType(objType)
{
}

Obj::~Obj()
{
}

void Obj::stopRefer(Item *item, StopReferInfo** sri)
{
	auto const newSri = new ObjStopReferInfo;
	newSri->setObj(this);
	newSri->reserve(m_conts.size());
	for ( auto const& pair : m_conts )
	{
		ContStopReferInfo* newContSri;
		pair.second->stopRefer(item, &newContSri);
		newSri->add(newContSri);
	}

	*sri = newSri;
}

void Obj::stopReferAll(StopReferInfo** sri)
{
	auto const newSri = new ObjStopReferInfo;
	newSri->setObj(this);
	newSri->reserve(m_conts.size());
	for ( auto const& pair : m_conts )
	{
		ContStopReferInfo* newContSri;
		pair.second->stopReferAll(&newContSri);
		newSri->add(newContSri);
	}

	*sri = newSri;
}

size_t Obj::referredItemsSize() const
{
	size_t r = 0;
	for ( auto const& pair : m_conts )
	{
		r += pair.second->referredItemsSize();
	}
	return r;
}

std::vector<Item *> Obj::referredItems() const
{
	std::vector<Item*> r;
	r.reserve(referredItemsSize());
	for ( auto const& pair : m_conts )
	{
		pair.second->referredItems(&r);
	}
	return r;
}

ItemTrack* Obj::createTrack(
		Track* parent,
		ItemTrackInfo const* trackInfo
		)
{
	return new ObjTrack(
				parent,
				this,
				toObjTrackInfo(trackInfo)
				);
}

const ItemType *Obj::itemType() const
{
	return m_objType;
}

const ObjType *Obj::objType() const
{
	return m_objType;
}

void Obj::addCont(Cont* cont)
{
	m_conts.emplace(cont->memberId(), cont);
}

bool Obj::has(MemberId id) const
{
	return m_conts.find(id) != m_conts.end();
}

Cont *Obj::cont(MemberId id)
{
	return m_conts.at(id).get();
}

ObjSubject *Obj::createObjSubject()
{
	auto const iter = m_subjects.insert(std::make_unique<ObjSubject>(this)).first;
	return (*iter).get();
}

void Obj::freeObjSubject(ObjSubject *subject)
{
	subject->emitExpired();
	for ( auto const& pair : m_conts )
	{
		pair.second->stopListen(subject);
	}
	m_subjects.erase(m_subjects.find(subject));
}

void Obj::freeAllObjSubjects()
{
	for ( auto const& subject : m_subjects )
	{
		subject->emitExpired();
	}
	for ( auto const& pair : m_conts )
	{
		pair.second->stopListenAll();
	}
	m_subjects.clear();
}

void Obj::handleItemEvent(const ItemEvent *event)
{
	switch ( event->type() )
	{
		case ItemEvent::Type::Expire_B:
			freeAllObjSubjects();
			break;
		default:
			break;
	}
}

}
