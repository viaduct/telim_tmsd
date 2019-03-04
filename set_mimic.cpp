#include "set_mimic.h"

#include "set_track.h"

#include "item_track.h"

#include "item_mimic.h"

namespace telimtmsd {

Track *SetMimic::track() const
{
	return m_track;
}

ContTrack *SetMimic::contTrack() const
{
	return m_track;
}

void SetMimic::setSetTrack(SetTrack *one)
{
	m_track = one;
}

SetTrack *SetMimic::setTrack() const
{
	return m_track;
}

Set *SetMimic::set() const
{
	return m_track->set();
}

size_t SetMimic::itemMimicsSize() const
{
	return m_track->itemTracksSize();
}

ItemMimic*SetMimic::itemMimic(size_t index) const
{
	return toItemMimic(m_track->itemTrack(index)->getMimic(key()));
}

std::vector<ItemMimic *> SetMimic::itemMimics() const
{
	std::vector<ItemMimic*> r;
	auto const size = itemMimicsSize();
	r.reserve(size);
	for ( size_t i = 0; i < size; ++i )
	{
		r.push_back(itemMimic(i));
	}
	return r;
}

size_t SetMimic::childrenSize() const
{
	return itemMimicsSize();
}

ItemMimic *SetMimic::child(size_t index) const
{
	return itemMimic(index);
}

std::vector<ItemMimic *> SetMimic::children() const
{
	return itemMimics();
}

void SetMimic::emit_add_b(size_t index, bool fromThis)
{
	handle_add_b(index, fromThis);
}

void SetMimic::emit_add_a(size_t index, bool fromThis)
{
	handle_add_a(index, fromThis);
}

void SetMimic::emit_remove_b(size_t index, bool fromThis)
{
	handle_remove_b(index, fromThis);
}

void SetMimic::emit_remove_a(size_t index, bool fromThis)
{
	handle_remove_a(index, fromThis);
}

void SetMimic::emit_clear_b(bool fromThis)
{
	handle_clear_b(fromThis);
}

void SetMimic::emit_clear_a(bool fromThis)
{
	handle_clear_a(fromThis);
}

void SetMimic::handle_add_b(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void SetMimic::handle_add_a(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void SetMimic::handle_remove_b(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void SetMimic::handle_remove_a(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void SetMimic::handle_clear_b(bool fromThis)
{
	(void)fromThis;
}

void SetMimic::handle_clear_a(bool fromThis)
{
	(void)fromThis;
}

}
