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
			SimpleContent(std::string &&name);
			SimpleContent(const SimpleContent &ano) = default;
			SimpleContent(SimpleContent &&ano) = default;
			SimpleContent &operator=(const SimpleContent &rhs) = default;
			SimpleContent &operator=(SimpleContent &&rhs) = default;
			~SimpleContent(void) = default;

			inline void setSimpleTypeName(const std::string &simpleTypeName) { m_simpleTypeName.assign(simpleTypeName); }
			inline void setSimpleTypeName(const std::string &&simpleTypeName) { m_simpleTypeName.assign(std::move(simpleTypeName)); }
			inline const std::string &getSimpleTypeName(void) const { return m_simpleTypeName; }

			std::set<std::string> neededTokens(void) const override;

		private:
			std::string m_simpleTypeName;
		};
	};
};
