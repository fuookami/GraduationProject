#pragma once

#include "VEDAModelFileBase.h"
#include "VEDAReportDataFile.h"

namespace VEDA
{
	class VEDAReportConfigurationFile : public VEDAModelFileBase, public IVEDAFileParentInterface<VEDAReportFile>, public IVEDAFileIndexInterface<VEDAReportDataFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAReportConfigurationFile> generate(const std::string &url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model = nullptr);
		static std::shared_ptr<VEDAReportConfigurationFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAReportConfigurationFile(const std::string &url);
	public:
		VEDAReportConfigurationFile(const VEDAReportConfigurationFile &ano) = delete;
		VEDAReportConfigurationFile(VEDAReportConfigurationFile &&ano) = delete;
		VEDAReportConfigurationFile &operator=(const VEDAReportConfigurationFile &rhs) = delete;
		VEDAReportConfigurationFile &operator=(VEDAReportConfigurationFile &&rhs) = delete;
		~VEDAReportConfigurationFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &IndexFileTag(void) const override;
	};
};
