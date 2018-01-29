#include "AttributeGroup.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		AttributeGroup::AttributeGroup(void)
			: IXSDNamedElementInterface(), IXSDReferenceElementInterface(), 
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(nullptr)
		{
		}

		AttributeGroup::AttributeGroup(const std::string & name)
			: IXSDNamedElementInterface(name), IXSDReferenceElementInterface(), 
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(nullptr)
		{
		}

		AttributeGroup::AttributeGroup(std::string && name)
			: IXSDNamedElementInterface(std::move(name)), IXSDReferenceElementInterface(), 
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(nullptr)
		{
		}

		AttributeGroup::AttributeGroup(const std::string & name, const std::shared_ptr<AttributeGroup>& base)
			: IXSDNamedElementInterface(name), IXSDReferenceElementInterface(),
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(base)
		{
		}

		AttributeGroup::AttributeGroup(std::string && name, const std::shared_ptr<AttributeGroup>& base)
			: IXSDNamedElementInterface(std::move(name)), IXSDReferenceElementInterface(),
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(base)
		{
		}

		inline const std::shared_ptr<Attribute> AttributeGroup::getAttribute(const std::string & name) const
		{
			auto it(m_attributes.find(name));
			return it != m_attributes.cend() ? it->second : nullptr;
		}

		inline const std::shared_ptr<AttributeGroup> AttributeGroup::getAttributeGroup(const std::string & name) const
		{
			auto it(m_attributeGroups.find(name));
			return it != m_attributeGroups.cend() ? it->second : nullptr;
		}

		const bool AttributeGroup::isAttrExist(const std::string & name) const
		{
			for (const auto &attrPair : m_attributes)
			{
				if (attrPair.first == name)
				{
					return true;
				}
			}

			for (const auto &groupPair : m_attributeGroups)
			{
				if (groupPair.second->isAttrExist(name))
				{
					return true;
				}
			}

			return false;
		}

		const bool AttributeGroup::isAttrGourpExist(const std::string & name) const
		{
			for (const auto &groupPair : m_attributeGroups)
			{
				if (groupPair.first == name)
				{
					return true;
				}
				else if (groupPair.second->isAttrGourpExist(name))
				{
					return true;
				}
			}

			return false;
		}
	};
};
