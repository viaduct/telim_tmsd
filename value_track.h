#pragma once
#include <map>
#include <memory>
#include "item_track.h"

namespace telimtmsd {

template <typename T> class Value;
template <typename T> class ValueSubject;
template <typename T> class ValueTrackInfo;
template <typename T> class ValueMimic;
template <typename T> class ValueEvent;

template <typename T>
class ValueTrack final : public ItemTrack
{
public:
	ValueTrack(
			Track* parent,
			Value<T>* value,
			ValueTrackInfo<T> const* trackInfo
			);

	TrackInfo const* trackInfo() const override;
	ItemTrackInfo const* itemTrackInfo() const override;
	Item* item() const override;
	ValueTrackInfo<T> const* valueTrackInfo() const;
	ValueSubject<T>* valueSubject() const;
	Value<T>* value() const;

	void mimic(int key, MimicryInfo* mInfo) override;
	void stopMimic(int key) override;
	void stopMimicAll() override;
	ValueMimic<T>* getValueMimic(int key);
	Mimic* getMimic(int key) override;
	ItemMimic* getItemMimic(int key) override;

protected:
	void start_impl() override;
	void stop_impl() override;

private:
	void handleValueEvent(ValueEvent<T> const* event);

	struct MimicPack final
	{
		MimicPack(ValueMimic<T>* mimic, MimicryInfo* info);
		std::unique_ptr<ValueMimic<T>> mimic;
		MimicryInfo* info;
	};
	std::map<int, MimicPack> m_mimics;
	Value<T>* m_value;
	ValueSubject<T>* m_subject;
	ValueTrackInfo<T> const* m_trackInfo;
};

}
