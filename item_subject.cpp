#include "item_subject.h"

namespace telimtmsd {

void ItemSubject::emitExpired()
{
	if ( m_subjectExpireCallback )
	{
		m_subjectExpireCallback();
	}
}

void ItemSubject::listenExpire(std::function<void ()> callback)
{
	m_subjectExpireCallback = std::move(callback);
}

void ItemSubject::stopListenExpire()
{
	m_subjectExpireCallback = nullptr;
}

}
