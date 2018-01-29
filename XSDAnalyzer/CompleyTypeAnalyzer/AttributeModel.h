#pragma once

#include "Attribute.h"
#include "AnyAttribute.h"
#include "AttributeGroup.h"

namespace XSDFrontend
{
	class AttributeModel
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

		inline void clear(void) { m_globalAttributes.clear(); m_attributeGroups.clear(); }

	public:
		static const std::string getNewDefaultAttributeGroupName(void);

	private:
		std::map<std::string, std::shared_ptr<Attribute::Attribute>> m_globalAttributes;
		std::map<std::string, std::shared_ptr<Attribute::AttributeGroup>> m_attributeGroups;
	};
};
