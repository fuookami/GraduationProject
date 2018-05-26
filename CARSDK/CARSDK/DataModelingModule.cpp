#include "stdafx.h"
#include "DataModelingModule.h"

namespace CARSDK
{
	std::shared_ptr<DataModelingModule> DataModelingModule::instance(void)
	{
		static std::shared_ptr<DataModelingModule> ret(new DataModelingModule());
		return ret;
	}

	std::shared_ptr<XSDFrontend::XSDModel> DataModelingModule::normalize(const std::vector<Info>& infos, const std::shared_ptr<XSDFrontend::XSDModel> originModel) const
	{
		return std::shared_ptr<XSDFrontend::XSDModel>();
	}

	std::vector<DataModelingModule::Info> DataModelingModule::analyze(const std::shared_ptr<XSDFrontend::XSDModel> model) const
	{
		return std::vector<Info>();
	}
};
