#pragma once

#include "Attribute.h"
#include "AnyAttribute.h"
#include "AttributeGroup.h"

namespace XSDFrontend
{
	class SSXSDUtils_API_DECLSPEC AttributeModel
	{
	public:
		AttributeModel(void) = default;
		AttributeModel(const AttributeModel &ano) = delete;
		AttributeModel(AttributeModel &&ano) = delete;
		AttributeModel &operator=(const AttributeModel &rhs) = delete;
		AttributeModel &operator=(AttributeModel &&rhs) = delete;
		~AttributeModel(void) = default;

		const std::shared_ptr<Attribute::Attribute> getGlobalAttribute(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<Attribute::Attribute>> &getGlobalAttributes(void) { return m_globalAttributes; }
		inline const std::map<std::string, std::shared_ptr<Attribute::Attribute>> &getGlobalAttributes(void) const { return m_globalAttributes; }

		const std::shared_ptr<Attribute::AttributeGroup> getAttributeGroup(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<Attribute::AttributeGroup>> &getAttributeGroups(void) { return m_attributeGroups; }
		inline const std::map<std::string, std::shared_ptr<Attribute::AttributeGroup>> &getAttributeGroups(void) const { return m_attributeGroups; }

		inline const bool isGlobalAttributeExist(const std::string &name) const { return m_globalAttributes.find(name) != m_globalAttributes.cend(); }
		inline const bool isAttributeGroupExist(const std::string &name) const { return m_attributeGroups.find(name) != m_attributeGroups.cend(); }

		inline const bool hasToken(const std::string &token) { return isGlobalAttributeExist(token) || isAttributeGroupExist(token); }
		inline void clear(void) { m_globalAttributes.clear(); m_attributeGroups.clear(); }

	public:
		std::string getNewDefaultAttributeGroupName(void) const;

	private:
		std::map<std::string, std::shared_ptr<Attribute::Attribute>> m_globalAttributes;
		std::map<std::string, std::shared_ptr<Attribute::AttributeGroup>> m_attributeGroups;
	};
};
