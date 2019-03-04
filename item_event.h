#pragma once

namespace telimtmsd {

class Item;

class ItemEvent
{
public:
	enum class Type : char
	{
//		Isolate_B,
//		Isolate_A,
		Expire_B
	};

	ItemEvent(Item* item) :
		m_item(item)
	{
	}

	auto type() const { return m_type; }
	void setType(Type value) { m_type = value; }

	Item* item() const { return m_item; }

private:
	Item* m_item;
	Type m_type;
};

}
