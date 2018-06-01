#pragma once

#include "VEDAFile.h"
#include "SSUtils/XSD/XSDModel.h"

namespace VEDA
{
	class VEDAModelFileBase abstract : public VEDAFile
	{
	protected:
		VEDAModelFileBase(const std::string &url, const Type type);
		
	public:
		VEDAModelFileBase(const VEDAModelFileBase &ano) = delete;
		VEDAModelFileBase(VEDAModelFileBase &&ano) = delete;
		VEDAModelFileBase &operator=(const VEDAModelFileBase &rhs) = delete;
		VEDAModelFileBase &operator=(VEDAModelFileBase &&rhs) = delete;
		virtual ~VEDAModelFileBase(void) = default;

		inline std::shared_ptr<XSDFrontend::XSDModel> getModel(void) { return m_model; }
		inline const std::shared_ptr<XSDFrontend::XSDModel> getModel(void) const { return m_model; }
		inline void setModel(const std::shared_ptr<XSDFrontend::XSDModel> model) { m_model = model; }

	protected:
		const bool init(const std::shared_ptr<SSUtils::XML::Node> indexNode, const std::shared_ptr<SSUtils::XML::Node> modelNode);
		const bool init(const VEDAFile &parentFile, const std::string & name);
		std::shared_ptr<SSUtils::XML::Node> normalizeModelParameter(std::shared_ptr<XSDFrontend::XSDModel> model = nullptr) const;

	protected:
		std::shared_ptr<XSDFrontend::XSDModel> m_model;
	};
};
