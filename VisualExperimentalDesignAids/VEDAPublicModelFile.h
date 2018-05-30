#pragma once

#include "VEDAModelFileBase.h"

namespace VEDA
{
	class VEDAPublicModelFile : public VEDAModelFileBase, public IVEDAFileParentInterface<VEDAProjectFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAPublicModelFile> generate(const std::string &url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model);
		static std::shared_ptr<VEDAPublicModelFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAPublicModelFile(const std::string &url);
	public:
		VEDAPublicModelFile(const VEDAPublicModelFile &ano) = delete;
		VEDAPublicModelFile(VEDAPublicModelFile &&ano) = delete;
		VEDAPublicModelFile &operator=(const VEDAPublicModelFile &rhs) = delete;
		VEDAPublicModelFile &operator=(VEDAPublicModelFile &&rhs) = delete;
		~VEDAPublicModelFile(void) = default;

		SSUtils::XML::Document toXML(void) const override;
	};
};
