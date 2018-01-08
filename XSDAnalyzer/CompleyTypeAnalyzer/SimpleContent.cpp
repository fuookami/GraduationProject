#include "SimpleContent.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		SimpleContent::SimpleContent(void)
			: IComplexTypeInterface(eComplexType::tSimpleContent), 
			m_simpleTypeName(), m_attributeGroupName()
		{
		}

		SimpleContent::SimpleContent(const std::string & name)
			: IComplexTypeInterface(name, eComplexType::tSimpleContent), 
			m_simpleTypeName(), m_attributeGroupName()
		{
		}

		SimpleContent::SimpleContent(const std::string && name)
			: IComplexTypeInterface(std::move(name), eComplexType::tSimpleContent), 
			m_simpleTypeName(), m_attributeGroupName()
		{
		}

		SimpleContent::SimpleContent(const SimpleContent & ano)
			: IComplexTypeInterface(ano), 
			m_simpleTypeName(ano.m_simpleTypeName), m_attributeGroupName(ano.m_attributeGroupName)
		{
		}

		SimpleContent::SimpleContent(const SimpleContent && ano)
			: IComplexTypeInterface(ano), 
			m_simpleTypeName(std::move(ano.m_simpleTypeName)), m_attributeGroupName(std::move(ano.m_attributeGroupName))
		{
		}

		SimpleContent & SimpleContent::operator=(const SimpleContent & rhs)
		{
			m_simpleTypeName.assign(rhs.m_simpleTypeName);
			m_attributeGroupName.assign(rhs.m_attributeGroupName);

			IComplexTypeInterface::operator=(rhs);

			return *this;
		}

		SimpleContent & SimpleContent::operator=(const SimpleContent && rhs)
		{
			m_simpleTypeName.assign(std::move(rhs.m_simpleTypeName));
			m_attributeGroupName.assign(std::move(rhs.m_attributeGroupName));

			IComplexTypeInterface::operator=(std::move(rhs));

			return *this;
		}

		SimpleContent::~SimpleContent(void)
		{
		}
	};
};
