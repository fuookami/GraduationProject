#include "stdafx.h"
#include "AttributeModel.h"

namespace XSDFrontend
{
	const std::shared_ptr<Attribute::Attribute> AttributeModel::getGlobalAttribute(const std::string & name) const
	{
		auto it(m_globalAttributes.find(name));
		return it != m_globalAttributes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<Attribute::AttributeGroup> AttributeModel::getAttributeGroup(const std::string & name) const
	{
		auto it(m_attributeGroups.find(name));
		return it != m_attributeGroups.cend() ? it->second : nullptr;
	}

	std::string AttributeModel::getNewDefaultAttributeGroupName(void) const
	{
		static unsigned int defaultNameNumber(0);
		static const std::string AttrubuteGroupNamePrefix("attribute_group_");

		do
		{
			++defaultNameNumber;
		} while (isAttributeGroupExist(AttrubuteGroupNamePrefix + std::to_string(defaultNameNumber)));
		
		return AttrubuteGroupNamePrefix + std::to_string(defaultNameNumber);
	}
};
