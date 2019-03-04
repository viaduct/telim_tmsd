#pragma once
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include "cont_track.h"

namespace telimtmsd {

class ItemTrack;
class Set;
class ContEvent;
class SetTrackInfo;
class ItemSubject;
class SetMimic;

class SetTrack final : public ContTrack
{
public:
	SetTrack(
			ObjTrack* objTrack,
			Set* set,
			SetTrackInfo const* trackInfo
			);
	virtual ~SetTrack();

	TrackInfo const* trackInfo() const override;
	ContTrackInfo const* contTrackInfo() const override;
	Cont* cont() const override;
	SetTrackInfo const* setTrackInfo() const;
	Set* set() const;

	template <typename T> typename Chain<T>::Track* itemTrack(size_t index)
	{
		return static_cast<typename Chain<T>::Track*>(itemTrack(index));
	}
	template <typename T> typename Chain<T>::Track* itemTrack(Item const* index)
	{
		return static_cast<typename Chain<T>::Track*>(itemTrack(index));
	}
	size_t itemTracksSize() const;
	ItemTrack* itemTrack(size_t index);
	ItemTrack* itemTrack(Item const* item);
	bool hasItemTrack(Item const* item) const;
	void forItemTracks(std::function<bool (ItemTrack*, size_t)> const& c);

	void mimic(int key, MimicryInfo* mInfo) override;
	void stopMimic(int key) override;
	void stopMimicAll() override;
	SetMimic* getSetMimic(int key);
	Mimic* getMimic(int key) override;
	ContMimic* getContMimic(int key) override;

protected:
	void start_impl() override;
	void stop_impl() override;

private:
	using Tracks = std::vector<std::unique_ptr<ItemTrack>>;

	void append(Item* item);
	void remove(Tracks::const_iterator iter);
	void loc(Item* item, Tracks::const_iterator* iterOut, size_t* indexOut) const;
	void catchUp();
	void clear();
	void handleContEvent(ContEvent const* event);

	struct MimicPack final
	{
		MimicPack(SetMimic* mimic, MimicryInfo* info);
		std::unique_ptr<SetMimic> mimic;
		MimicryInfo* info;
	};
	std::map<int, MimicPack> m_mimics;

	Tracks m_tracks;

	size_t m_addIndex, m_removeIndex; // Used in handleContEvent(), for optimization.

	Set* m_cont;
	SetTrackInfo const* m_trackInfo;
};

}
