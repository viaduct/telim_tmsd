#pragma once
#include <vector>
#include <cstddef>
#include "cont_mimic.h"

namespace telimtmsd {

class List;
class ListTrack;

class ListMimic : public ContMimic
{
public:
	Track* track() const override final;
	ContTrack* contTrack() const override final;

	using ContMimic::ContMimic;

	void setListTrack(ListTrack* one);

	ListTrack* listTrack() const;
	List* list() const;

	size_t itemMimicsSize() const;
	ItemMimic* itemMimic(size_t index) const;
	std::vector<ItemMimic*> itemMimics() const;

	size_t childrenSize() const;
	ItemMimic* child(size_t index) const;
	std::vector<ItemMimic*> children() const;

	void emit_add_b(size_t index, bool fromThis);
	void emit_add_a(size_t index, bool fromThis);
	void emit_remove_b(size_t from, size_t hm, bool fromThis);
	void emit_remove_a(size_t from, size_t hm, bool fromThis);
	void emit_move_b(size_t from, size_t hm, size_t to, bool fromThis);
	void emit_move_a(size_t from, size_t hm, size_t to, bool fromThis);
	void emit_clear_b(bool fromThis);
	void emit_clear_a(bool fromThis);

protected:
	virtual void handle_add_b(size_t index, bool fromThis);
	virtual void handle_add_a(size_t index, bool fromThis);
	virtual void handle_remove_b(size_t from, size_t hm, bool fromThis);
	virtual void handle_remove_a(size_t from, size_t hm, bool fromThis);
	virtual void handle_move_b(size_t from, size_t hm, size_t to, bool fromThis);
	virtual void handle_move_a(size_t from, size_t hm, size_t to, bool fromThis);
	virtual void handle_clear_b(bool fromThis);
	virtual void handle_clear_a(bool fromThis);

private:
	ListTrack* m_track;
};

template <typename T>
inline ListMimic* toListMimic(T* one) { return static_cast<ListMimic*>(one); }
}
