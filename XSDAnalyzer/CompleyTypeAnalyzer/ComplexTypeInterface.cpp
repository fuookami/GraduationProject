#include "ComplexTypeInterface.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		IComplexTypeInterface::IComplexTypeInterface(const eComplexType type)
			: IXSDNamedElementInterface(), 
			m_type(type), m_deriveType(eDerivedType::tNone), m_baseTypeName()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const std::string & name, const eComplexType type)
			: IXSDNamedElementInterface(name), 
			m_type(type), m_deriveType(eDerivedType::tNone), m_baseTypeName()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const std::string && name, const eComplexType type)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_deriveType(eDerivedType::tNone), m_baseTypeName()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const IComplexTypeInterface & ano)
			: IXSDNamedElementInterface(ano), 
			m_type(ano.m_type), m_deriveType(ano.m_deriveType), m_baseTypeName(ano.m_baseTypeName)
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const IComplexTypeInterface && ano)
			: IXSDNamedElementInterface(std::move(ano)), 
			m_type(ano.m_type), m_deriveType(ano.m_deriveType), m_baseTypeName(std::move(ano.m_baseTypeName))
		{
		}

		IComplexTypeInterface & IComplexTypeInterface::operator=(const IComplexTypeInterface & rhs)
		{
			m_type = rhs.m_type;
			m_deriveType = rhs.m_deriveType;
			m_baseTypeName.assign(rhs.m_baseTypeName);

			IXSDNamedElementInterface::operator=(rhs);

			return *this;
		}

		IComplexTypeInterface & IComplexTypeInterface::operator=(const IComplexTypeInterface && rhs)
		{
			m_type = rhs.m_type;
			m_deriveType = rhs.m_deriveType;
			m_baseTypeName.assign(std::move(rhs.m_baseTypeName));

			IXSDNamedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		IComplexTypeInterface::~IComplexTypeInterface(void)
		{
		}
	};
};
