#include "XSDParentedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		IXSDParentedElementInterface::IXSDParentedElementInterface(void)
			: m_parentType(eParentType::tNonParent), m_parentName()
		{
		}

		IXSDParentedElementInterface::IXSDParentedElementInterface(const IXSDParentedElementInterface & ano)
			: m_parentType(ano.m_parentType), m_parentName(ano.m_parentName)
		{
		}

		IXSDParentedElementInterface::IXSDParentedElementInterface(const IXSDParentedElementInterface && ano)
			: m_parentType(ano.m_parentType), m_parentName(std::move(ano.m_parentName))
		{
		}

		IXSDParentedElementInterface & IXSDParentedElementInterface::operator=(const IXSDParentedElementInterface & rhs)
		{
			m_parentType = rhs.m_parentType;
			m_parentName.assign(rhs.m_parentName);

			return *this;
		}

		IXSDParentedElementInterface & IXSDParentedElementInterface::operator=(const IXSDParentedElementInterface && rhs)
		{
			m_parentType = rhs.m_parentType;
			m_parentName.assign(std::move(rhs.m_parentName));

			return *this;
		}

		IXSDParentedElementInterface::~IXSDParentedElementInterface(void)
		{
		}
	};
};
