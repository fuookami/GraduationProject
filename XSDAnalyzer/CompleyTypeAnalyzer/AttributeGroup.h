#pragma once

#include "Attribute.h"
#include "AnyAttribute.h"

#include <map>
#include <memory>

namespace XSDFrontend
{
	namespace Attribute
	{
		class AttributeGroup : public XSDElementUtils::IXSDNamedElementInterface,
			public XSDElementUtils::IXSDReferenceElementInterface<AttributeGroup>
		{
		public:
			AttributeGroup(void);
			AttributeGroup(const std::string &name);
			AttributeGroup(std::string &&name);
			AttributeGroup(const std::string &name, const std::shared_ptr<AttributeGroup> &base);
			AttributeGroup(std::string &&name, const std::shared_ptr<AttributeGroup> &base);
			AttributeGroup(const AttributeGroup &ano) = default;
			AttributeGroup(AttributeGroup &&ano) = default;
			AttributeGroup &operator=(const AttributeGroup &rhs) = default;
			AttributeGroup &operator=(AttributeGroup &&rhs) = default;
			~AttributeGroup(void) = default;

			inline void setOrAddAttribute(const std::shared_ptr<Attribute> attr) { m_attributes[attr->hasRef() ? attr->getRefName() : attr->getName()] = attr; }
			inline void removeAttribute(const std::string &name) { if (hasAttribute(name)) m_attributes.erase(name); }
			inline const bool hasAttribute(const std::string &name) const { return isAttrExist(name); }
			inline const std::shared_ptr<Attribute> getAttribute(const std::string &name) const;

			inline void addAttributeGroup(const std::shared_ptr<AttributeGroup> &group) { m_attributeGroups[group->hasRef() ? group->getRefName() : group->getName()] = group; }
			inline void removeAttributeGroup(const std::string &name) { m_attributeGroups.erase(name); }
			inline const bool hasAttributeGroup(const std::string &name) const { return isAttrGourpExist(name); }
			inline const std::shared_ptr<AttributeGroup> getAttributeGroup(const std::string &name) const;

			inline void setAnyAttribute(const AnyAttribute &anyAttribute) { m_anyAttribute.reset(new AnyAttribute(anyAttribute)); }
			inline void setAnyAttribute(const AnyAttribute &&anyAttribute) { m_anyAttribute.reset(new AnyAttribute(std::move(anyAttribute))); }
			inline void removeAnyAttribute(void) { return m_anyAttribute.reset(); }
			inline const bool hasAnyAttribute(void) const { return m_anyAttribute != nullptr; }
			inline const std::shared_ptr<const AnyAttribute> getAnyAttribute(void) const { return m_anyAttribute; }

			inline void setBaseAttributeGroup(const std::shared_ptr<AttributeGroup> &baseGroup) { m_baseAttributeGroup = baseGroup; }
			inline void removeBaseAttributeGroup(void) { m_baseAttributeGroup.reset(); }
			inline const bool hasBaseAttributeGroup(void) const { return m_baseAttributeGroup != nullptr; }
			inline const std::shared_ptr<AttributeGroup> getAttributeGroup(void) const { return m_baseAttributeGroup; }

		private:
			const bool isAttrExist(const std::string &name) const;
			const bool isAttrGourpExist(const std::string &name) const;

		private:
			std::map<std::string, std::shared_ptr<Attribute>> m_attributes;
			std::map<std::string, std::shared_ptr<AttributeGroup>> m_attributeGroups;
			std::shared_ptr<const AnyAttribute> m_anyAttribute;

			std::shared_ptr<AttributeGroup> m_baseAttributeGroup;
		};
	};
};
