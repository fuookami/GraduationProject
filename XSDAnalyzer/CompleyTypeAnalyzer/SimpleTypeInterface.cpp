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

		const std::map<std::string, ISimpleTypeInterface::eWhiteSpace> WhiteSpaceString2WhiteSpace =
		{
			std::make_pair(std::string("preserve"), ISimpleTypeInterface::eWhiteSpace::Preserve),
			std::make_pair(std::string("replace"), ISimpleTypeInterface::eWhiteSpace::Replace),
			std::make_pair(std::string("collapse"), ISimpleTypeInterface::eWhiteSpace::Collapse)
		};
	};
};
