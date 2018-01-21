#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DatetimeUtils::Datetime ValueLimitConfiguration<DatetimeUtils::Datetime>::NoValueValidator(INT16_MIN, static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));

		DatetimeType::DatetimeType(void)
			: DatetimeType("")
		{
		}

		DatetimeType::DatetimeType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
		}

		DatetimeType::DatetimeType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType)
		{
		}

		DatetimeType::DatetimeType(const DatetimeType & ano)
			: ISimpleTypeInterface(ano), ValueLimitConfiguration(ano), ValueEnumrationConfiguration(ano), 
			m_baseType(ano.m_baseType)
		{
		}

		DatetimeType::DatetimeType(const DatetimeType && ano)
			: ISimpleTypeInterface(std::move(ano)), ValueLimitConfiguration(std::move(ano)), ValueEnumrationConfiguration(std::move(ano)),
			m_baseType(ano.m_baseType)
		{
		}

		DatetimeType & DatetimeType::operator=(const DatetimeType & rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(rhs);
			ValueLimitConfiguration::operator=(rhs);
			ValueEnumrationConfiguration::operator=(rhs);

			return *this;
		}

		DatetimeType & DatetimeType::operator=(const DatetimeType && rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(std::move(rhs));
			ValueLimitConfiguration::operator=(std::move(rhs));
			ValueEnumrationConfiguration::operator=(std::move(rhs));

			return *this;
		}

		DatetimeType::~DatetimeType(void)
		{
		}

		void DatetimeType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
