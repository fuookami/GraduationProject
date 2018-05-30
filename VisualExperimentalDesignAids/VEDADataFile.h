#pragma once

#include "VEDADataFileBase.h"
#include "SSUtils/XSD/XSDModel.h"

namespace VEDA
{
	class VEDADataFile : public VEDADataFileBase, public IVEDAFileParentInterface<VEDAOperationFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDADataFile> generate(const std::string &url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data);
		static std::shared_ptr<VEDADataFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDADataFile(const std::string &url);
	public:
		VEDADataFile(const VEDADataFile &ano) = delete;
		VEDADataFile(VEDADataFile &&ano) = delete;
		VEDADataFile &operator=(const VEDADataFile &rhs) = delete;
		VEDADataFile &operator=(VEDADataFile &&rhs) = delete;
		~VEDADataFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &DataNodeTag(void) const override;
	};
};
