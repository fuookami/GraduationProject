#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DatetimeUtils::DatetimeMs ValueLimitConfiguration<DatetimeUtils::DatetimeMs>::NoValueValidator(DatetimeUtils::DatetimeMs::EmptyDatetime);

		const ValueLimitConfiguration<DatetimeUtils::DatetimeMs>::TranslateFunction ValueLimitConfiguration<DatetimeUtils::DatetimeMs>::translator = XSDString2Datetime;
		const ValueEnumrationConfiguration<DatetimeUtils::DatetimeMs>::TranslateFunction ValueEnumrationConfiguration<DatetimeUtils::DatetimeMs>::translator = XSDString2Datetime;

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
