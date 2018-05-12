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
			ComplexContent(std::string &&name);
			ComplexContent(const ComplexContent &ano) = default;
			ComplexContent(ComplexContent &&ano) = default;
			ComplexContent &operator=(const ComplexContent &rhs) = default;
			ComplexContent &operator=(ComplexContent &&rhs) = default;
			~ComplexContent(void) = default;

			inline void setElementGroupName(const std::string &elementGroupName) { m_elementGroup.assign(elementGroupName); }
			inline void setElementGroupName(const std::string &&elementGroupName) { m_elementGroup.assign(std::move(elementGroupName)); }
			inline const std::string &getElementGroupName(void) const { return m_elementGroup; }

			std::set<std::string> neededTokens(void) const override;

		private:
			std::string m_elementGroup;
		};
	};
};
