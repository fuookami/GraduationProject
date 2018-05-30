#pragma once

#include "VEDAFile.h"
#include "SSUtils/XSD/XSDModel.h"

namespace VEDA
{
	class VEDADataFileBase abstract : public VEDAFile
	{
	protected:
		VEDADataFileBase(const std::string &url, const Type type);

	public:
		VEDADataFileBase(const VEDADataFileBase &ano) = delete;
		VEDADataFileBase(VEDADataFileBase &&ano) = delete;
		VEDADataFileBase &operator=(const VEDADataFileBase &rhs) = delete;
		VEDADataFileBase &operator=(VEDADataFileBase &&rhs) = delete;
		virtual ~VEDADataFileBase(void) = default;

		inline std::shared_ptr<XSDFrontend::XSDModel> getModel(void) { return m_model; }
		inline const std::shared_ptr<XSDFrontend::XSDModel> getModel(void) const { return m_model; }
		inline void setModel(const std::shared_ptr<XSDFrontend::XSDModel> model) { m_model = model; }

		inline std::shared_ptr<SSUtils::XML::Node> getData(void) { return m_data; }
		inline const std::shared_ptr<SSUtils::XML::Node> getData(void) const { return m_data; }
		inline void setData(const std::shared_ptr<SSUtils::XML::Node> data) { m_data = data; }

	protected:
		virtual const std::string &DataNodeTag(void) const = 0;
		const bool init(const std::shared_ptr<SSUtils::XML::Node> indexNode, const std::shared_ptr<SSUtils::XML::Node> modelNode, const std::shared_ptr<SSUtils::XML::Node> dataNode);
		const bool init(const VEDAFile &parentFile, const std::string & name);
		std::shared_ptr<SSUtils::XML::Node> normalizeModelParameter(void) const;

	protected:
		std::shared_ptr<XSDFrontend::XSDModel> m_model;
		std::shared_ptr<SSUtils::XML::Node> m_data;
	};
};
