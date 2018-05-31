#pragma once

#include "VEDADataFileBase.h"

namespace VEDA
{
	class VEDAReportDataFile : public VEDADataFileBase, public IVEDAFileParentInterface<VEDAReportConfigurationFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAReportDataFile> generate(const std::string &url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data);
		static std::shared_ptr<VEDAReportDataFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAReportDataFile(const std::string &url);
	public:
		VEDAReportDataFile(const VEDAReportDataFile &ano) = delete;
		VEDAReportDataFile(VEDAReportDataFile &&ano) = delete;
		VEDAReportDataFile &operator=(const VEDAReportDataFile &rhs) = delete;
		VEDAReportDataFile &operator=(VEDAReportDataFile &&rhs) = delete;
		~VEDAReportDataFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &DataNodeTag(void) const override;
	};
};
