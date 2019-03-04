#pragma once
#include "mimic.h"

namespace telimtmsd {

class ContTrack;
class ItemMimic;

class ContMimic : public Mimic
{
public:
	using Mimic::Mimic;

	virtual ContTrack* contTrack() const = 0;

	virtual bool isUniqueChildValid() const;
	virtual ItemMimic* uniqueChild();
};

template <typename T>
inline ContMimic* toContMimic(T* one) { return static_cast<ContMimic*>(one); }

}
