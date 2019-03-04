#pragma once
#include <functional>
#include "member_id.h"
#include "item_subject.h"

namespace telimtmsd {

class Obj;
class ContEvent;

class ObjSubject final : public ItemSubject
{
public:
	ObjSubject(Obj* obj);

	Item* item() const override;

	Obj* obj() const { return m_obj; }

	void listenCont(MemberId id, std::function<void (ContEvent const*)> callback);
	void stopListen(MemberId id);

	void freeThis() override;

private:
	Obj* m_obj;
};

template <typename T>
inline ObjSubject* toObjSubject(T* subject) { return static_cast<ObjSubject*>(subject); }

}
