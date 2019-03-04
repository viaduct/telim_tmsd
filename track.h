#pragma once
#include "track_id.h"
#include "chain.h"

namespace telimtmsd {

class MimicryInfo;
class TrackInfo;
class Mimic;

class Track
{
public:
	Track(Track* parent);
	Track() = default;
	Track(Track const&) = delete;
	Track& operator =(Track const&) = delete;
	virtual ~Track() = default;

	virtual TrackInfo const* trackInfo() const = 0;

	Track* parent() const;
	TrackId trackId() const;

	void start();
	void stop();

	template <typename T> typename Chain<T>::Mimic* getMimic(int key)
	{
		return static_cast<typename Chain<T>::Mimic*>(getMimic(key));
	}
	virtual void mimic(int key, MimicryInfo* mInfo) = 0;
	virtual void stopMimic(int key) = 0;
	virtual void stopMimicAll() = 0;
	virtual Mimic* getMimic(int key) = 0;

protected:
	virtual void start_impl() = 0;
	virtual void stop_impl() = 0;

private:
	Track* m_parent;
};

}
