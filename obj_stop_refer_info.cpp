#include "obj_stop_refer_info.h"

#include "cont_stop_refer_info.h"

namespace telimtmsd {

ObjStopReferInfo::ObjStopReferInfo()
{
}

ObjStopReferInfo::~ObjStopReferInfo()
{
}

void ObjStopReferInfo::stop() const
{
	for ( auto const& info : m_infos )
	{
		info->stop();
	}
}

void ObjStopReferInfo::rollback() const
{
	for ( auto const& info : m_infos )
	{
		info->rollback();
	}
}

Obj*ObjStopReferInfo::obj() const
{
	return m_obj;
}

void ObjStopReferInfo::forContStopReferInfos(std::function<bool (const ContStopReferInfo*)> c) const
{
	bool resume = true;
	for ( auto i = m_infos.begin(); resume && i != m_infos.end(); ++i )
	{
		resume = c((*i).get());
	}
}

void ObjStopReferInfo::setObj(Obj* one)
{
	m_obj = one;
}

void ObjStopReferInfo::reserve(size_t size)
{
	m_infos.reserve(size);
}

void ObjStopReferInfo::add(ContStopReferInfo* one)
{
	m_infos.emplace_back(one);
}

}
