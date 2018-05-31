#pragma once

#include "VEDAFile.h"
#include "VEDAReportConfigurationFile.h"

namespace VEDA
{
	class VEDAReportFile : public VEDAFile, public IVEDAFileParentInterface<VEDAProjectFile>, public IVEDAFileIndexInterface<VEDAReportConfigurationFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAReportFile> generate(const std::string &url, const VEDAFile &parentFile);
		static std::shared_ptr<VEDAReportFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAReportFile(const std::string &url);
	public:
		VEDAReportFile(const VEDAReportFile &ano) = delete;
		VEDAReportFile(VEDAReportFile &&ANO) = delete;
		VEDAReportFile &operator=(const VEDAReportFile &rhs) = delete;
		VEDAReportFile &operator=(VEDAReportFile &&rhs) = delete;
		~VEDAReportFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &IndexFileTag(void) const override;
	};
};
