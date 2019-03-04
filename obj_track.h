#pragma once
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include "item_track.h"
#include "member_id.h"

namespace telimtmsd {

class Obj;
class ObjSubject;
class MimicryInfo;
class ContTrack;
class Subject;
class ObjTrackInfo;
class ObjMimic;

class ObjTrack final : public ItemTrack
{
public:
	ObjTrack(
			Track* parent,
			Obj* obj,
			ObjTrackInfo const* trackInfo
			);
	virtual ~ObjTrack();

	TrackInfo const* trackInfo() const override;
	ItemTrackInfo const* itemTrackInfo() const override;
	Item* item() const override;
	ObjTrackInfo const* objTrackInfo() const;
	ObjSubject* objSubject() const;
	Obj* obj() const;

	template <typename T> typename Chain<T>::Track* contTrack(MemberId mid)
	{
		return static_cast<typename Chain<T>::Track*>(contTrack(mid));
	}
	template <typename T> typename Chain<T>::Track* contTrack_safe(MemberId mid)
	{
		return static_cast<typename Chain<T>::Track*>(contTrack_safe(mid));
	}
	ContTrack* contTrack(MemberId mid);
	ContTrack* contTrack_safe(MemberId mid);
	bool hasContTrack(MemberId mid) const;
	void forContTracks(std::function<bool (MemberId, ContTrack*)> const& c);
	std::vector<std::tuple<MemberId, ContTrack*>> contTracks();
	size_t contTracksSize() const;

	void mimic(int key, MimicryInfo* mInfo) override;
	void stopMimic(int key) override;
	void stopMimicAll() override;
	ObjMimic* getObjMimic(int key);
	Mimic* getMimic(int key) override;
	ItemMimic* getItemMimic(int key) override;

protected:
	void start_impl() override;
	void stop_impl() override;

private:
	struct MimicPack final
	{
		MimicPack(ObjMimic* mimic,MimicryInfo* info);
		std::unique_ptr<ObjMimic> mimic;
		MimicryInfo* info;
	};
	std::map<int, MimicPack> m_mimics;

	std::map<MemberId, std::unique_ptr<ContTrack>> m_contTracks;
	Obj* m_obj;
	ObjSubject* m_subject;
	ObjTrackInfo const* m_trackInfo;
};

template <typename T>
inline ObjTrack* toObjTrack(T track) { return static_cast<ObjTrack*>(track); }

}
