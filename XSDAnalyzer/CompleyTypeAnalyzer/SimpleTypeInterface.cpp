#include "SimpleTypeInterface.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		ISimpleTypeInterface::ISimpleTypeInterface(const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const std::string & name, const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(name), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(std::string && name, const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}
	};
};
