#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "stop_refer_info.h"

namespace telimtmsd {

class Obj;
class ContStopReferInfo;

class ObjStopReferInfo final : public StopReferInfo
{
public:
	ObjStopReferInfo();
	virtual ~ObjStopReferInfo();

	void stop() const override;
	void rollback() const override;

	Obj* obj() const;
	void forContStopReferInfos(std::function<bool (ContStopReferInfo const*)> c) const;

	void setObj(Obj* one);
	void reserve(size_t size);
	void add(ContStopReferInfo* one);

private:
	std::vector<std::unique_ptr<ContStopReferInfo>> m_infos;
	Obj* m_obj;
};

}
