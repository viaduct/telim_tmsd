#pragma once
#include "track.h"
#include "member_id.h"
#include "cont_type.h"

namespace telimtmsd {

class Item;
class Obj;
class ObjTrack;
class ObjSubject;
class MimicryInfo;
class ContTrackInfo;
class ContMimic;

class ContTrack : public Track
{
public:
	ContTrack(
			ObjTrack* objTrack
			);
	virtual ~ContTrack();
	ContTrack(ContTrack const&) = delete;
	ContTrack& operator =(ContTrack const&) = delete;

	virtual ContTrackInfo const* contTrackInfo() const = 0;
	virtual Cont* cont() const = 0;

	virtual ContMimic* getContMimic(int key) = 0;

	ObjTrack* objTrack() const;
	ObjSubject* objSubject() const;
	Obj* obj() const;
	MemberId memberId() const;
};

}
