#include "DateTimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DateTimeUtils::DateTime ValueLimitConfiguration<DateTimeUtils::DateTime>::NoValueValidator(INT16_MIN, static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));

		DateTimeType::DateTimeType(void)
			: DateTimeType("")
		{
		}

		DateTimeType::DateTimeType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDateTimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
		}

		DateTimeType::DateTimeType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDateTimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType)
		{
		}

		DateTimeType::DateTimeType(const DateTimeType & ano)
			: ISimpleTypeInterface(ano), ValueLimitConfiguration(ano), ValueEnumrationConfiguration(ano), 
			m_baseType(ano.m_baseType)
		{
		}

		DateTimeType::DateTimeType(const DateTimeType && ano)
			: ISimpleTypeInterface(std::move(ano)), ValueLimitConfiguration(std::move(ano)), ValueEnumrationConfiguration(std::move(ano)),
			m_baseType(ano.m_baseType)
		{
		}

		DateTimeType & DateTimeType::operator=(const DateTimeType & rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(rhs);
			ValueLimitConfiguration::operator=(rhs);
			ValueEnumrationConfiguration::operator=(rhs);

			return *this;
		}

		DateTimeType & DateTimeType::operator=(const DateTimeType && rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(std::move(rhs));
			ValueLimitConfiguration::operator=(std::move(rhs));
			ValueEnumrationConfiguration::operator=(std::move(rhs));

			return *this;
		}

		DateTimeType::~DateTimeType(void)
		{
		}

		void DateTimeType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
