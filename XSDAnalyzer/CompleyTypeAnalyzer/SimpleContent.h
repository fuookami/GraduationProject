#pragma once

#include "ComplexTypeInterface.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		class SimpleContent final : public IComplexTypeInterface                    
		{
		public:
			SimpleContent(void);
			SimpleContent(const std::string &name);
			SimpleContent(const std::string &&name);
			SimpleContent(const SimpleContent &ano);
			SimpleContent(const SimpleContent &&ano);
			SimpleContent &operator=(const SimpleContent &rhs);
			SimpleContent &operator=(const SimpleContent &&rhs);
			~SimpleContent(void);

			inline void setSimpleTypeName(const std::string &simpleTypeName) { m_simpleTypeName.assign(simpleTypeName); }
			inline void setSimpleTypeName(const std::string &&simpleTypeName) { m_simpleTypeName.assign(std::move(simpleTypeName)); }
			inline const std::string &getSimpleTypeName(void) const { return m_simpleTypeName; }

			inline void setAttributeGroupName(const std::string &attributeGroupName) { m_attributeGroupName.assign(attributeGroupName); }
			inline void setAttributeGroupName(const std::string &&attributeGroupName) { m_attributeGroupName.assign(std::move(attributeGroupName)); }
			inline const std::string &getAttributeGroupName(void) const { return m_attributeGroupName; }

		private:
			std::string m_simpleTypeName;
			std::string m_attributeGroupName;
		};
	};
};
