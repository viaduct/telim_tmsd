#pragma once
#include <cassert>
#include <stack>
#include <memory>
#include "../item_rtti.h"
#include "../track_id.h"
#include "../member_id.h"
#include "../cont_type.h"
#include "item.h"
#include "bundle.h"

namespace telimtmsd_comps {

namespace tmsd = telimtmsd;

class Composer
{
public:
	using ItemRtti = tmsd::ItemRtti;
	using TrackId = tmsd::TrackId;
	using MemberId = tmsd::MemberId;
	using ContType = tmsd::ContType;

	class State;
	class ItemState;
	class BundleState;

	class State
	{
	public:
		State(Composer* owner) : m_owner(owner) {}
		State(State const&) = delete;
		State& operator =(State const&) = delete;
		virtual ~State() = default;

		virtual void When(ItemRtti) const { assert(false); }
		virtual void Default() const { assert(false); }
		virtual void NoDefault() const { assert(false); }
		virtual void IdIs(TrackId) const { assert(false); }
		virtual void TrackMember(MemberId, ContType) const { assert(false); }
		virtual void End() const { m_owner->popState(); }

	protected:
		Composer* owner() const { return m_owner; }
	private:
		Composer* m_owner;
	};
	class BundleState final : public State
	{
	public:
		BundleState(Composer* owner, Bundle* bundle) :
			State(owner),
			m_bundle(bundle)
		{
		}

		void When(ItemRtti irtti) const override
		{
			auto const item = new Item;
			m_bundle->add(irtti, item);
			owner()->pushItemState(item);
		}
		void Default() const override
		{
			auto const item = new Item;
			m_bundle->setDefault(item);
			owner()->pushItemState(item);
		}
		void NoDefault() const override
		{
		}
	private:
		Bundle* m_bundle;
	};
	class ItemState final : public State
	{
	public:
		ItemState(Composer* owner, Item* item) :
			State(owner), m_item(item)
		{
		}

		void IdIs(TrackId tid) const override
		{
			m_item->setTrackId(tid);
		}
		void TrackMember(MemberId mid, ContType contType) const override
		{
			auto const bundle = new Bundle;
			m_item->addMember(mid, contType, bundle);
			owner()->pushBundleState(bundle);
		}
	public:
		Item* m_item;
	};

	Composer() = default;
	Composer(Composer const&) = delete;
	Composer& operator =(Composer const&) = delete;

	void When(ItemRtti irtti) { state()->When(irtti); }
	void Default() { state()->Default(); }
	void NoDefault() { state()->NoDefault(); }
	void IdIs(TrackId tid) { state()->IdIs(tid); }
	void TrackMember(MemberId mid, ContType contType) { state()->TrackMember(mid, contType); }
	void End() { state()->End(); }

	void compose(Bundle* bundle)
	{
		pushBundleState(bundle);

		run();

		popState();
	}

protected:
	virtual void run() = 0;

private:
	State* state() { return m_states.top().get(); }
	void pushItemState(Item* item)
	{
		m_states.push(std::make_unique<ItemState>(this, item));
	}
	void pushBundleState(Bundle* bundle)
	{
		m_states.push(std::make_unique<BundleState>(this, bundle));
	}
	void popState()
	{
		m_states.pop();
	}

	std::stack<std::unique_ptr<State>> m_states;
};

}
