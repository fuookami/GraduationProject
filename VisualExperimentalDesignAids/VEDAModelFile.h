#pragma once

#include "VEDAModelFileBase.h"

namespace VEDA
{
	class VEDAModelFile : public VEDAModelFileBase, public IVEDAFileParentInterface<VEDAProcessFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAModelFile> generate(const std::string &url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model);
		static std::shared_ptr<VEDAModelFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAModelFile(const std::string &url);
	public:
		VEDAModelFile(const VEDAModelFile &ano) = delete;
		VEDAModelFile(VEDAModelFile &&ano) = delete;
		VEDAModelFile &operator=(const VEDAModelFile &rhs) = delete;
		VEDAModelFile &operator=(VEDAModelFile &&rhs) = delete;
		~VEDAModelFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;
	};
};
