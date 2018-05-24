#pragma once

#include "SimpleTypeModel.h"
#include "AttributeModel.h"
#include "ComplexTypeModel.h"

namespace XSDFrontend
{
	class SSXSDUtils_API_DECLSPEC XSDModel
	{
	public:
		static const std::shared_ptr<XSDModel> generateNewXSDModel(void);

	private:
		XSDModel(void);
	public:
		XSDModel(const XSDModel &ano) = delete;
		XSDModel(XSDModel &&ano) = delete;
		XSDModel &operator=(const XSDModel &rhs) = delete;
		XSDModel &operator=(XSDModel &&rhs) = delete;
		~XSDModel(void) = default;

	public:
		inline const std::shared_ptr<SimpleTypeModel> getSimpleTypeModel(void) const { return m_simpleTypeModel; }
		inline const std::shared_ptr<AttributeModel> getAttributeModel(void) const { return m_attributeModel; }
		inline const std::shared_ptr<ComplexTypeModel> getComplexTypeModel(void) const { return m_complexTypeMode; }

		inline const bool hasToken(const std::string &token) { return m_simpleTypeModel->hasToken(token) || m_attributeModel->hasToken(token) || m_complexTypeMode->hasToken(token); }
		inline void clear(void) { m_simpleTypeModel->clear(); m_attributeModel->clear(); m_complexTypeMode->clear(); }

		inline void setDescription(const std::string &description, const std::string &lang = std::string("cn")) { m_description.assign(description); m_descriptionLang.assign(lang); }
		inline void setDescription(std::string &&description, const std::string &lang = std::string("cn")) { m_description.assign(std::move(description)); m_descriptionLang .assign(lang); }
		inline const std::string &getDescription(void) const { return m_description; }
		inline const std::string &getDescriptionLang(void) const { return m_descriptionLang; }

		std::shared_ptr<SSUtils::XML::Node> generateXSDRoot(void);

	private:
		std::shared_ptr<SimpleTypeModel> m_simpleTypeModel;
		std::shared_ptr<AttributeModel> m_attributeModel;
		std::shared_ptr<ComplexTypeModel> m_complexTypeMode;

		std::string m_description;
		std::string m_descriptionLang;
	};
};
