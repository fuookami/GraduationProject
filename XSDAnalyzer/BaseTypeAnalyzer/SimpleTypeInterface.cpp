#include "SimpleTypeInterface.h"

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		ISimpleTypeInterface::ISimpleTypeInterface(const eSimpleType type, const eWhiteSpace whitSpace)
			: m_name(), m_type(type), m_whiteSpace(whitSpace), m_baseTypeName(), m_description()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const std::string & name, const eSimpleType type, const eWhiteSpace whitSpace)
			: m_name(name), m_type(type), m_whiteSpace(whitSpace), m_baseTypeName(), m_description()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const std::string && name, const eSimpleType type, const eWhiteSpace whitSpace)
			: m_name(std::move(name)), m_type(type), m_whiteSpace(whitSpace), m_baseTypeName(), m_description()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const ISimpleTypeInterface & ano)
			: m_name(ano.m_name), m_type(ano.m_type), m_whiteSpace(ano.m_whiteSpace), m_baseTypeName(ano.m_baseTypeName), m_description(ano.m_description)
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const ISimpleTypeInterface && ano)
			: m_name(std::move(ano.m_name)), m_type(ano.m_type), m_whiteSpace(ano.m_whiteSpace), m_baseTypeName(std::move(ano.m_baseTypeName)), m_description(std::move(ano.m_description))
		{
		}

		ISimpleTypeInterface & ISimpleTypeInterface::operator=(const ISimpleTypeInterface & rhs)
		{
			m_name.assign(rhs.m_name);
			m_type = rhs.m_type;
			m_whiteSpace = rhs.m_whiteSpace;
			m_baseTypeName.assign(rhs.m_baseTypeName);
			m_description.assign(rhs.m_description);

			return *this;
		}

		ISimpleTypeInterface & ISimpleTypeInterface::operator=(const ISimpleTypeInterface && rhs)
		{
			m_name.assign(std::move(rhs.m_name));
			m_type = rhs.m_type;
			m_whiteSpace = rhs.m_whiteSpace;
			m_baseTypeName.assign(std::move(rhs.m_baseTypeName));
			m_description.assign(std::move(rhs.m_description));

			return *this;
		}

		ISimpleTypeInterface::~ISimpleTypeInterface(void)
		{
		}
	};
};
