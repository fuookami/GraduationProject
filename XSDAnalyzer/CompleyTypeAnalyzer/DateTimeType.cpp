#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DatetimeUtils::Datetime ValueLimitConfiguration<DatetimeUtils::Datetime>::NoValueValidator(DatetimeUtils::Datetime::EmptyDatetime);

		const ValueLimitConfiguration<DatetimeUtils::Datetime>::TranslateFunction ValueLimitConfiguration<DatetimeUtils::Datetime>::translator = XSDString2NumberVairant;
		const ValueEnumrationConfiguration<DatetimeUtils::Datetime>::TranslateFunction ValueEnumrationConfiguration<DatetimeUtils::Datetime>::translator = XSDString2NumberVairant;

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

		DatetimeUtils::Datetime XSDString2Datetime(const std::string & str)
		{
			//! to do
			return DatetimeUtils::Datetime();
		}
	};
};
