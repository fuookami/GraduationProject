#include "stdafx.h"
#include "SimpleContent.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		SimpleContent::SimpleContent(void)
			: IComplexTypeInterface(eComplexType::tSimpleContent), 
			m_simpleTypeName()
		{
		}

		SimpleContent::SimpleContent(const std::string & name)
			: IComplexTypeInterface(name, eComplexType::tSimpleContent), 
			m_simpleTypeName()
		{
		}

		SimpleContent::SimpleContent(std::string && name)
			: IComplexTypeInterface(std::move(name), eComplexType::tSimpleContent), 
			m_simpleTypeName()
		{
		}

		std::set<std::string> SimpleContent::neededTokens(void) const
		{
			auto ret = IComplexTypeInterface::neededTokens();
			if (!m_simpleTypeName.empty())
			{
				ret.insert(m_simpleTypeName);
			}
			return ret;
		}
	};
};
