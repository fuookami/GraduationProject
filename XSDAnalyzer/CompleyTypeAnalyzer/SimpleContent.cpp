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
	};
};
