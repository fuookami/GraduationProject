#include "StringType.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		StringType::StringType(void)
			: StringType("")
		{
		}

		StringType::StringType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_pattern()
		{
		}

		StringType::StringType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType), m_pattern()
		{
		}

		StringType::StringType(const StringType & ano)
			: ISimpleTypeInterface(ano), LengthLimitConfiguration(ano), ValueEnumrationConfiguration(ano), 
			m_baseType(ano.m_baseType), m_pattern(ano.m_pattern)
		{
		}

		StringType::StringType(const StringType && ano)
			: ISimpleTypeInterface(std::move(ano)), LengthLimitConfiguration(ano), ValueEnumrationConfiguration(std::move(ano)), 
			m_baseType(ano.m_baseType), m_pattern(ano.m_pattern)
		{
		}

		StringType & StringType::operator=(const StringType & rhs)
		{
			m_baseType = rhs.m_baseType;
			m_pattern.assign(rhs.m_pattern);

			ISimpleTypeInterface::operator=(rhs);
			LengthLimitConfiguration::operator=(rhs);
			ValueEnumrationConfiguration::operator=(rhs);

			return *this;
		}

		StringType & StringType::operator=(const StringType && rhs)
		{
			m_baseType = rhs.m_baseType;
			m_pattern = rhs.m_pattern;

			ISimpleTypeInterface::operator=(std::move(rhs));
			LengthLimitConfiguration::operator=(std::move(rhs));
			ValueEnumrationConfiguration::operator=(std::move(rhs));

			return *this;
		}

		StringType::~StringType(void)
		{
		}

		void StringType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
