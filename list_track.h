#pragma once
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include "cont_track.h"

namespace telimtmsd {

class ItemTrack;
class List;
class ContEvent;
class ListTrackInfo;
class ItemSubject;
class ListMimic;

class ListTrack final : public ContTrack
{
public:
	ListTrack(
			ObjTrack* objTrack,
			List* list,
			ListTrackInfo const* trackInfo
			);
	virtual ~ListTrack();

	TrackInfo const* trackInfo() const override;
	ContTrackInfo const* contTrackInfo() const override;
	Cont* cont() const override;
	ListTrackInfo const* listTrackInfo() const;
	List* list() const;

	template <typename T> typename Chain<T>::Track* itemTrack(size_t index)
	{
		return static_cast<typename Chain<T>::Track*>(itemTrack(index));
	}
	size_t itemTracksSize() const;
	ItemTrack* itemTrack(size_t index);
	void forItemTracks(std::function<bool (ItemTrack*, size_t)> const& c);

	void mimic(int key, MimicryInfo* mInfo) override;
	void stopMimic(int key) override;
	void stopMimicAll() override;
	ListMimic* getListMimic(int key);
	Mimic* getMimic(int key) override;
	ContMimic* getContMimic(int key) override;

protected:
	void start_impl() override;
	void stop_impl() override;

private:
	void insert(Item* item, size_t index);
	void remove(size_t index, size_t howMany);
	void move(size_t from, size_t howMany, size_t to);
	void catchUp();
	void clear();

	void handleContEvent(ContEvent const* event);

	struct MimicPack final
	{
		MimicPack(ListMimic* mimic, MimicryInfo* info);
		std::unique_ptr<ListMimic> mimic;
		MimicryInfo* info;
	};
	std::map<int, MimicPack> m_mimics;

	std::vector<std::unique_ptr<ItemTrack>> m_tracks;
	List* m_cont;
	ListTrackInfo const* m_trackInfo;
};

}
