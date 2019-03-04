#include "list_mimic.h"

#include "list_track.h"

#include "item_track.h"

#include "item_mimic.h"

namespace telimtmsd {

Track *ListMimic::track() const
{
	return m_track;
}

ContTrack *ListMimic::contTrack() const
{
	return m_track;
}

void ListMimic::setListTrack(ListTrack *one)
{
	m_track = one;
}

ListTrack *ListMimic::listTrack() const
{
	return m_track;
}

List *ListMimic::list() const { return m_track->list(); }

size_t ListMimic::itemMimicsSize() const
{
	return m_track->itemTracksSize();
}

ItemMimic*ListMimic::itemMimic(size_t index) const
{
	return toItemMimic(m_track->itemTrack(index)->getMimic(key()));
}

std::vector<ItemMimic *> ListMimic::itemMimics() const
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

size_t ListMimic::childrenSize() const
{
	return itemMimicsSize();
}

ItemMimic *ListMimic::child(size_t index) const
{
	return itemMimic(index);
}

std::vector<ItemMimic *> ListMimic::children() const
{
	return itemMimics();
}

void ListMimic::emit_add_b(size_t index, bool fromThis)
{
	handle_add_b(index, fromThis);
}

void ListMimic::emit_add_a(size_t index, bool fromThis)
{
	handle_add_a(index, fromThis);
}

void ListMimic::emit_remove_b(size_t from, size_t hm, bool fromThis)
{
	handle_remove_b(from, hm, fromThis);
}

void ListMimic::emit_remove_a(size_t from, size_t hm, bool fromThis)
{
	handle_remove_a(from, hm, fromThis);
}

void ListMimic::emit_move_b(size_t from, size_t hm, size_t to, bool fromThis)
{
	handle_move_b(from, hm, to, fromThis);
}

void ListMimic::emit_move_a(size_t from, size_t hm, size_t to, bool fromThis)
{
	handle_move_a(from, hm, to, fromThis);
}

void ListMimic::emit_clear_b(bool fromThis)
{
	handle_clear_b(fromThis);
}

void ListMimic::emit_clear_a(bool fromThis)
{
	handle_clear_a(fromThis);
}

void ListMimic::handle_add_b(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void ListMimic::handle_add_a(size_t index, bool fromThis)
{
	(void)index, (void)fromThis;
}

void ListMimic::handle_remove_b(size_t from, size_t hm, bool fromThis)
{
	(void)from, (void)hm, (void)fromThis;
}

void ListMimic::handle_remove_a(size_t from, size_t hm, bool fromThis)
{
	(void)from, (void)hm, (void)fromThis;
}

void ListMimic::handle_move_b(size_t from, size_t hm, size_t to, bool fromThis)
{
	(void)from, (void)hm, (void)to, (void)fromThis;
}

void ListMimic::handle_move_a(size_t from, size_t hm, size_t to, bool fromThis)
{
	(void)from, (void)hm, (void)to, (void)fromThis;
}

void ListMimic::handle_clear_b(bool fromThis)
{
	(void)fromThis;
}

void ListMimic::handle_clear_a(bool fromThis)
{
	(void)fromThis;
}

}
