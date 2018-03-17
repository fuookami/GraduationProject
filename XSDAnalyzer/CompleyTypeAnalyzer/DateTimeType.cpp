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

		const std::map<std::string, DatetimeType::eBaseType> DatetimeBaseTypeName2Type =
		{
			std::make_pair(std::string("date"), DatetimeType::eBaseType::tDate),
			std::make_pair(std::string("time"), DatetimeType::eBaseType::tTime),
			std::make_pair(std::string("dateTime"), DatetimeType::eBaseType::tDatetime),
			std::make_pair(std::string("gYear"), DatetimeType::eBaseType::gYear),
			std::make_pair(std::string("gYearMonth"), DatetimeType::eBaseType::gYearMonth),
			std::make_pair(std::string("gMonth"), DatetimeType::eBaseType::gMonth),
			std::make_pair(std::string("gMonthDay"), DatetimeType::eBaseType::gMonthDay),
			std::make_pair(std::string("gDay"), DatetimeType::eBaseType::gDay),
			std::make_pair(std::string("duration"), DatetimeType::eBaseType::tDuration)
		};

		DatetimeUtils::Datetime XSDString2Datetime(const std::string & str)
		{
			// 正则匹配（记得要加终止符）
			// YYYY-MM-DD
			// hh:mm:ss.sss
			// YYYY-MM-DDThh:mm:ss.sss
			// YYYY
			// YYYY-MM
			// --MM
			// --MM-DD
			// ---DDD
			// PnYnMnDTnHnMnS
			return DatetimeUtils::Datetime();
		}
	};
};
