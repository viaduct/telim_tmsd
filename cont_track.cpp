#include <cassert>

#include "cont_track.h"

#include "obj_track.h"

#include "obj_subject.h"

#include "single_track.h"
#include "set_track.h"
#include "list_track.h"

#include "cont_track_info.h"

namespace telimtmsd {

ContTrack::ContTrack(
		ObjTrack* objTrack
		) :
	Track(objTrack)
{
}

ContTrack::~ContTrack()
{
}

ObjTrack *ContTrack::objTrack() const
{
	return toObjTrack(parent());
}

ObjSubject *ContTrack::objSubject() const
{
	return objTrack()->objSubject();
}

Obj *ContTrack::obj() const
{
	return objTrack()->obj();
}

MemberId ContTrack::memberId() const
{
	return contTrackInfo()->memberId();
}

}
