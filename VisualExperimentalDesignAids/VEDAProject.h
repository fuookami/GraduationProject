#pragma once

#include "XMLUtils.h"

namespace VEDA
{
	class VEDAProcess;

	class VEDAProject
	{
	public:
		static std::shared_ptr<VEDAProject> generate(const std::string &name);
		static std::shared_ptr<VEDAProject> generate(std::string &&name);

	private:
		VEDAProject(const std::string &name);
		VEDAProject(std::string &&name);
		void init(void);
		
	public:
		VEDAProject(const VEDAProject &ano) = delete;
		VEDAProject(VEDAProject &&ano) = delete;
		~VEDAProject(void);

		XMLUtils::XMLNode toXML(void);
	};
};
