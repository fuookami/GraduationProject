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

		ISimpleTypeInterface::ISimpleTypeInterface(const std::string && name, const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const ISimpleTypeInterface & ano)
			: IXSDNamedElementInterface(ano), 
			m_type(ano.m_type), m_whiteSpace(ano.m_whiteSpace), m_baseTypeName(ano.m_baseTypeName)
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const ISimpleTypeInterface && ano)
			: IXSDNamedElementInterface(std::move(ano)), 
			m_type(ano.m_type), m_whiteSpace(ano.m_whiteSpace), m_baseTypeName(std::move(ano.m_baseTypeName))
		{
		}

		ISimpleTypeInterface & ISimpleTypeInterface::operator=(const ISimpleTypeInterface & rhs)
		{
			m_type = rhs.m_type;
			m_whiteSpace = rhs.m_whiteSpace;
			m_baseTypeName.assign(rhs.m_baseTypeName);

			IXSDNamedElementInterface::operator=(rhs);

			return *this;
		}

		ISimpleTypeInterface & ISimpleTypeInterface::operator=(const ISimpleTypeInterface && rhs)
		{
			m_type = rhs.m_type;
			m_whiteSpace = rhs.m_whiteSpace;
			m_baseTypeName.assign(std::move(rhs.m_baseTypeName));

			IXSDNamedElementInterface::operator=(std::move(rhs));

			return *this;
		}

		ISimpleTypeInterface::~ISimpleTypeInterface(void)
		{
		}
	};
};
