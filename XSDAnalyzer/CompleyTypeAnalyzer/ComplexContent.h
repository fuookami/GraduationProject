#pragma once

#include "ComplexTypeInterface.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		class ComplexContent final : public IComplexTypeInterface
		{
		public:
			ComplexContent(void);
			ComplexContent(const std::string &name);
			ComplexContent(const std::string &&name);
			ComplexContent(const ComplexContent &ano);
			ComplexContent(const ComplexContent &&ano);
			ComplexContent &operator=(const ComplexContent &rhs);
			ComplexContent &operator=(const ComplexContent &&rhs);
			~ComplexContent(void);

			inline void setElementGroupName(const std::string &elementGroupName) { m_elementGroup.assign(elementGroupName); }
			inline void setElementGroupName(const std::string &&elementGroupName) { m_elementGroup.assign(std::move(elementGroupName)); }
			inline const std::string &getElementGroupName(void) const { return m_elementGroup; }

			inline void setAttributeGroupName(const std::string &attributeGroupName) { m_attributeGroup.assign(attributeGroupName); }
			inline void setAttributeGroupName(const std::string &&attributeGroupName) { m_attributeGroup.assign(std::move(attributeGroupName)); }
			inline const std::string &getAttributeGroupName(void) const { return m_attributeGroup; }

		private:
			std::string m_elementGroup;
			std::string m_attributeGroup;
		};
	};
};
