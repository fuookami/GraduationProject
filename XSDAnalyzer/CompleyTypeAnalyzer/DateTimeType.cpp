#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const DatetimeType::value_type ValueLimitConfiguration<DatetimeType::value_type>::NoValueValidator(SSUtils::Datetime::Datetime::EmptyDatetime);

		DatetimeType::DatetimeType(void)
			: DatetimeType("")
		{
		}

		DatetimeType::DatetimeType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
			ValueLimitConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
		}

		DatetimeType::DatetimeType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType)
		{
			ValueLimitConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
		}

		const bool DatetimeType::refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			if (!refreshValueLimitConfiguration(node, std::bind(XSDString2Datetime, m_baseType, std::placeholders::_1)))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node, std::bind(XSDString2Datetime, m_baseType, std::placeholders::_1));

			return true;
		}

		void DatetimeType::setBaseType(const eBaseType baseType)
		{
			m_baseType = baseType;
			ValueLimitConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<value_type>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
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

		DatetimeType::value_type XSDString2Datetime(const DatetimeType::eBaseType type, const std::string & str)
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
			return DatetimeType::value_type();
		}
	};
};
