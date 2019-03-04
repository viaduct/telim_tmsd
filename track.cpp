#include "track.h"

#include "track_info.h"

namespace telimtmsd {

Track::Track(Track *parent) :
	m_parent(parent)
{
}

Track *Track::parent() const
{
	return m_parent;
}

TrackId Track::trackId() const
{
	return trackInfo()->trackId();
}

void Track::start()
{
	start_impl();
}

void Track::stop()
{
	stop_impl();
}

}
