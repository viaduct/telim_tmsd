#include "single_mimic.h"

#include "single_track.h"

#include "item_track.h"

#include "item_mimic.h"

namespace telimtmsd {

Track *SingleMimic::track() const
{
	return m_track;
}

ContTrack *SingleMimic::contTrack() const
{
	return m_track;
}

bool SingleMimic::isUniqueChildValid() const
{
	return isItemMimicValid();
}

ItemMimic *SingleMimic::uniqueChild()
{
	return child();
}

void SingleMimic::setSingleTrack(SingleTrack *one)
{
	m_track = one;
}

SingleTrack *SingleMimic::singleTrack() const
{
	return m_track;
}

Single *SingleMimic::single() const
{
	return m_track->single();
}

bool SingleMimic::isItemMimicValid() const
{
	return m_track->isItemTrackValid();
}

ItemMimic*SingleMimic::itemMimic() const
{
	return toItemMimic(m_track->itemTrack()->getMimic(key()));
}

bool SingleMimic::isChildValid() const
{
	return isItemMimicValid();
}

ItemMimic *SingleMimic::child() const
{
	return itemMimic();
}

void SingleMimic::emit_validSet_b(bool fromThis)
{
	handle_validSet_b(fromThis);
}

void SingleMimic::emit_validSet_a(bool fromThis)
{
	handle_validSet_a(fromThis);
}

void SingleMimic::emit_nullSet_b(bool fromThis)
{
	handle_nullSet_b(fromThis);
}

void SingleMimic::emit_nullSet_a(bool fromThis)
{
	handle_nullSet_a(fromThis);
}

void SingleMimic::handle_validSet_b(bool fromThis)
{
	(void)fromThis;
}

void SingleMimic::handle_validSet_a(bool fromThis)
{
	(void)fromThis;
}

void SingleMimic::handle_nullSet_b(bool fromThis)
{
	(void)fromThis;
}

void SingleMimic::handle_nullSet_a(bool fromThis)
{
	(void)fromThis;
}

}
