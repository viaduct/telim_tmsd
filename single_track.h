#pragma once
#include <memory>
#include <map>
#include "cont_track.h"

namespace telimtmsd {

class ItemTrack;
class Single;
class ContEvent;
class SingleTrackInfo;
class ItemSubject;
class SingleMimic;

class SingleTrack final : public ContTrack
{
public:
	SingleTrack(
			ObjTrack* objTrack,
			Single* single,
			SingleTrackInfo const* trackInfo
			);
	virtual ~SingleTrack();

	TrackInfo const* trackInfo() const override;
	ContTrackInfo const* contTrackInfo() const override;
	Cont* cont() const override;
	SingleTrackInfo const* singleTrackInfo() const;
	Single* single() const;

	template <typename T> typename Chain<T>::Track* itemTrack()
	{
		return static_cast<typename Chain<T>::Track*>(itemTrack());
	}
	bool isItemTrackValid() const;
	ItemTrack* itemTrack();

	void mimic(int key, MimicryInfo* mInfo) override;
	void stopMimic(int key) override;
	void stopMimicAll() override;
	SingleMimic* getSingleMimic(int key);
	Mimic* getMimic(int key) override;
	ContMimic* getContMimic(int key) override;

protected:
	void start_impl() override;
	void stop_impl() override;

private:
	void handleContEvent(ContEvent const* event);
	void setValidItemTrack(Item* item);
	void setNullItemTrack();

	struct MimicPack final
	{
		MimicPack(SingleMimic* mimic, MimicryInfo* info);
		std::unique_ptr<SingleMimic> mimic;
		MimicryInfo* info;
	};
	std::map<int, MimicPack> m_mimics;

	std::unique_ptr<ItemTrack> m_track;
	Single* m_cont;
	SingleTrackInfo const* m_trackInfo;
};

}
