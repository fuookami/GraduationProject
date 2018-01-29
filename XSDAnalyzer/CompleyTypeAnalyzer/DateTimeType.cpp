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

		DatetimeType::DatetimeType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType)
		{
		}

		void DatetimeType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
