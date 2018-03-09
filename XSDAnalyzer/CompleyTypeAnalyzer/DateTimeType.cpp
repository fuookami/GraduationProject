#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DatetimeUtils::Datetime ValueLimitConfiguration<DatetimeUtils::Datetime>::NoValueValidator(DatetimeUtils::Datetime::EmptyDatetime);

		const ValueLimitConfiguration<DatetimeUtils::Datetime>::TranslateFunction ValueLimitConfiguration<DatetimeUtils::Datetime>::translator = XSDString2Datetime;
		const ValueEnumrationConfiguration<DatetimeUtils::Datetime>::TranslateFunction ValueEnumrationConfiguration<DatetimeUtils::Datetime>::translator = XSDString2Datetime;

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

		const bool DatetimeType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			if (!refreshValueLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node);

			return true;
		}

		DatetimeUtils::Datetime XSDString2Datetime(const std::string & str)
		{
			//! to do
			return DatetimeUtils::Datetime();
		}
	};
};
