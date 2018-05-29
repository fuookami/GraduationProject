#pragma once

#include "SSUtils\XSD\XSDModel.h"

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
		~VEDAProject(void) = default;

		inline std::map<std::string, VEDAProcess> &processes(void) { return m_processes; }
		inline const std::map<std::string, VEDAProcess> &processes(void) const { return m_processes; }

		SSUtils::XML::Document toXML(void);
		static std::shared_ptr<VEDAProject> fromXML(const SSUtils::XML::Document &doc);

	private:
		std::string m_publicDataModelFileName;

		std::map<std::string, VEDAProcess> m_processes;
	};
};
