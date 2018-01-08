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

		AttributeGroup::AttributeGroup(const std::string && name)
			: IXSDNamedElementInterface(std::move(name)), IXSDReferenceElementInterface(), 
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(nullptr)
		{
		}

		AttributeGroup::AttributeGroup(const std::string & name, const std::shared_ptr<AttributeGroup>& base)
			: IXSDNamedElementInterface(name), IXSDReferenceElementInterface(),
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(base)
		{
		}

		AttributeGroup::AttributeGroup(const std::string && name, const std::shared_ptr<AttributeGroup>& base)
			: IXSDNamedElementInterface(std::move(name)), IXSDReferenceElementInterface(),
			m_attributes(), m_attributeGroups(), m_anyAttribute(nullptr), m_baseAttributeGroup(base)
		{
		}

		AttributeGroup::AttributeGroup(const AttributeGroup & ano)
			: IXSDNamedElementInterface(ano), IXSDReferenceElementInterface(ano), 
			m_attributes(ano.m_attributes), m_attributeGroups(ano.m_attributeGroups), m_anyAttribute(new AnyAttribute(*ano.m_anyAttribute)), m_baseAttributeGroup(ano.m_baseAttributeGroup)
		{
		}

		AttributeGroup::AttributeGroup(const AttributeGroup && ano)
			: IXSDNamedElementInterface(std::move(ano)), IXSDReferenceElementInterface(std::move(ano)),
			m_attributes(std::move(ano.m_attributes)), m_attributeGroups(std::move(ano.m_attributeGroups)), m_anyAttribute(new AnyAttribute(*ano.m_anyAttribute)), m_baseAttributeGroup(ano.m_baseAttributeGroup)
		{
		}

		AttributeGroup & AttributeGroup::operator=(const AttributeGroup & rhs)
		{
			m_attributes = rhs.m_attributes;
			m_attributeGroups = rhs.m_attributeGroups;
			m_anyAttribute.reset(new AnyAttribute(*rhs.m_anyAttribute));
			m_baseAttributeGroup = rhs.m_baseAttributeGroup;

			IXSDNamedElementInterface::operator=(rhs);
			IXSDReferenceElementInterface::operator=(rhs);

			return *this;
		}

		AttributeGroup & AttributeGroup::operator=(const AttributeGroup && rhs)
		{
			m_attributes = std::move(rhs.m_attributes);
			m_attributeGroups = std::move(rhs.m_attributeGroups);
			m_anyAttribute = rhs.m_anyAttribute;
			m_baseAttributeGroup = rhs.m_baseAttributeGroup;

			IXSDNamedElementInterface::operator=(std::move(rhs));
			IXSDReferenceElementInterface::operator=(std::move(rhs));

			return *this;
		}

		AttributeGroup::~AttributeGroup(void)
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
