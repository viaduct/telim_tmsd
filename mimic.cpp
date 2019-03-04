#include "mimic.h"

#include "track.h"

namespace telimtmsd {

Mimic*Mimic::parent() const
{
	return track()->parent()->getMimic(key());
}

int Mimic::key() const
{
	return m_key;
}

void Mimic::setKey(int one)
{
	m_key = one;
}

void *Mimic::userPtr() const
{
	return m_userPtr;
}

void Mimic::setUserPtr(void *ptr)
{
	m_userPtr = ptr;
}

}
