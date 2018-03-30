#include "VEDAProject.h"

namespace VEDA
{
	std::shared_ptr<VEDAProject> VEDAProject::generate(const std::string & name)
	{
		return std::make_shared<VEDAProject>(new VEDAProject(name));
	}

	std::shared_ptr<VEDAProject> VEDAProject::generate(std::string && name)
	{
		return std::make_shared<VEDAProject>(new VEDAProject(std::move(name)));
	}

};

