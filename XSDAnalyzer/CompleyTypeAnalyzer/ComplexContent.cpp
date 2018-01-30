#include "ComplexContent.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		ComplexContent::ComplexContent(void)
			: IComplexTypeInterface(eComplexType::tComplexContent), 
			m_elementGroup(), m_attributeGroup()
		{
		}

		ComplexContent::ComplexContent(const std::string & name)
			: IComplexTypeInterface(name, eComplexType::tComplexContent), 
			m_elementGroup(), m_attributeGroup()
		{
		}

		ComplexContent::ComplexContent(std::string && name)
			: IComplexTypeInterface(std::move(name), eComplexType::tComplexContent), 
			m_elementGroup(), m_attributeGroup()
		{
		}
	};
};
