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

		ComplexContent::ComplexContent(const std::string && name)
			: IComplexTypeInterface(std::move(name), eComplexType::tComplexContent), 
			m_elementGroup(), m_attributeGroup()
		{
		}

		ComplexContent::ComplexContent(const ComplexContent & ano)
			: IComplexTypeInterface(ano), 
			m_elementGroup(ano.m_elementGroup), m_attributeGroup(ano.m_attributeGroup)
		{
		}

		ComplexContent::ComplexContent(const ComplexContent && ano)
			: IComplexTypeInterface(std::move(ano)), 
			m_elementGroup(std::move(ano.m_elementGroup)), m_attributeGroup(std::move(ano.m_attributeGroup))
		{
		}

		ComplexContent & ComplexContent::operator=(const ComplexContent & rhs)
		{
			m_elementGroup.assign(rhs.m_elementGroup);
			m_attributeGroup.assign(rhs.m_attributeGroup);

			IComplexTypeInterface::operator=(rhs);

			return *this;
		}

		ComplexContent & ComplexContent::operator=(const ComplexContent && rhs)
		{
			m_elementGroup.assign(std::move(rhs.m_elementGroup));
			m_attributeGroup.assign(std::move(rhs.m_attributeGroup));

			IComplexTypeInterface::operator=(std::move(rhs));

			return *this;
		}

		ComplexContent::~ComplexContent(void)
		{
		}
	};
};
