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

		IComplexTypeInterface::IComplexTypeInterface(std::string && name, const eComplexType type)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_deriveType(eDerivedType::tNone), m_baseTypeName()
		{
		}
	};
};
