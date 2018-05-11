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

		std::set<std::string> AttributeGroup::suppliedTokens(void) const
		{
			std::set<std::string> ret;
			ret.insert(getName());
			return ret;
		}

		std::set<std::string> AttributeGroup::neededTokens(void) const
		{
			std::set<std::string> ret;
			for (const auto &pair : m_attributes)
			{
				if (pair.second->hasRef())
				{
					ret.insert(pair.second->getRefName());
				}
			}
			for (const auto &pair : m_attributeGroups)
			{
				if (pair.second->hasRef())
				{
					ret.insert(pair.second->getRefName());
				}
			}
			return ret;
		}

		const bool AttributeGroup::empty(void) const
		{
			return m_attributes.empty() && m_attributeGroups.empty() && m_anyAttribute == nullptr 
				&& (m_baseAttributeGroup == nullptr || m_baseAttributeGroup->empty());
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
