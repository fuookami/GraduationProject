#pragma once

#include "VEDAFile.h"
#include "SSUtils/XSD/XSDModel.h"

namespace VEDA
{
	class VEDADataFile : public VEDAFile
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDADataFile> generate(const std::string &url, const VEDAFile &parentFile);
		static std::shared_ptr<VEDADataFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDADataFile(const std::string &url);
	public:
		VEDADataFile(const VEDADataFile &ano) = delete;
		VEDADataFile(VEDADataFile &&ano) = delete;
		VEDADataFile &operator=(const VEDADataFile &rhs) = delete;
		VEDADataFile &operator=(VEDADataFile &&rhs) = delete;
		~VEDADataFile(void) = default;

		inline std::shared_ptr<XSDFrontend::XSDModel> getModel(void) { return m_model; }
		inline const std::shared_ptr<XSDFrontend::XSDModel> getModel(void) const { return m_model; }
		inline void setModel(const std::shared_ptr<XSDFrontend::XSDModel> model) { m_model = model; }

		inline std::shared_ptr<XSDFrontend::XSDModel> getModel(void) { return m_model; }
		inline const std::shared_ptr<SSUtils::XML::Node> getData(void) const { return m_data; }
		inline void setData(const std::shared_ptr<SSUtils::XML::Node> data) { m_data = data; }

		SSUtils::XML::Document toXML(void) const;

	private:
		std::shared_ptr<XSDFrontend::XSDModel> m_model;
		std::shared_ptr<SSUtils::XML::Node> m_data;
	};
};
