#pragma once
#include <list>
#include <memory>
#include "../track_id.h"
#include "../member_id.h"
#include "../cont_type.h"

namespace telimtmsd_comps {

namespace tmsd = telimtmsd;

class Bundle;

class Item final
{
public:
	using TrackId = tmsd::TrackId;
	using MemberId = tmsd::MemberId;
	using ContType = tmsd::ContType;

	Item(TrackId tid = 0) :
		m_trackId(tid)
	{
	}

	auto trackId() const { return m_trackId; }
	void setTrackId(TrackId tid) { m_trackId = tid; }

	void addMember(
			MemberId mid,
			ContType contType,
			Bundle* pack
			)
	{
		m_packs.emplace_back(mid, contType, pack);
	}
	template <typename C> void forBundles(C const& c) const;

private:
	struct Pack final
	{
		Pack(
				MemberId mid,
				ContType contType,
				Bundle* bundle
				);
		~Pack();

		std::unique_ptr<Bundle> bundle;
		MemberId mid;
		ContType contType;
	};
	std::list<Pack> m_packs;
	TrackId m_trackId;
};

template <typename C> void Item::forBundles(C const& c) const
{
	for ( auto const& pack : m_packs )
	{
		c(
					pack.mid,
					pack.contType,
					const_cast<Bundle const*>(pack.bundle.get())
					);
	}
}


}
