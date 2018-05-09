#include "DatetimeType.h"

#include <cstdint>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const SSUtils::Datetime::DatetimeDuration ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>::NoValueValidator = SSUtils::Datetime::DatetimeDuration();

		const std::map<std::string, DatetimeType::eBaseType> DatetimeType::String2Type =
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

		const std::map<DatetimeType::eBaseType, std::string> DatetimeType::Type2String =
			[]()
		{
			std::map<DatetimeType::eBaseType, std::string> ret;
			for (const auto &pair : DatetimeType::String2Type)
			{
				ret.insert(std::make_pair(pair.second, pair.first));
			}
			return ret;
		}();
		
		const std::map<DatetimeType::eBaseType, std::pair<std::string, std::string>> DatetimeType::Type2Pattern =
		{
			// YYYY-MM-DD
			std::make_pair(DatetimeType::eBaseType::tDate, std::make_pair(std::string("YYYY-MM-DD"), std::string("^(-?\\d{1,4})-(\\d{1,2})-(\\d{1,2})$"))),
			// hh:mm:ss.sss
			std::make_pair(DatetimeType::eBaseType::tTime, std::make_pair(std::string("hh:mm:ss.sss"), std::string("^(\\d{1,2}):(\\d{1,2}):(\\d{1,2}).(\\d{1,3})$"))),
			// YYYY-MM-DDThh:mm:ss.sss
			std::make_pair(DatetimeType::eBaseType::tTime, std::make_pair(std::string("YYYY-MM-DDThh:mm:ss.sss"), std::string("^(-?\\d{1,4})-(\\d{1,2})-(\\d{1,2})T(\\d{1,2}):(\\d{1,2}):(\\d{1,2}).(\\d{1,3})$"))),
			// YYYY
			std::make_pair(DatetimeType::eBaseType::gYear, std::make_pair(std::string("YYYY"), std::string("^(-?\\d{1,4})$"))),
			// YYYY-MM
			std::make_pair(DatetimeType::eBaseType::gYearMonth, std::make_pair(std::string("YYYY-MM"), std::string("^(-?\\d{1,4})-(\\d{1,2})$"))),
			// --MM
			std::make_pair(DatetimeType::eBaseType::gMonth, std::make_pair(std::string("--MM"), std::string("^--(\\d{1,2})$"))),
			// --MM-DD
			std::make_pair(DatetimeType::eBaseType::gMonthDay, std::make_pair(std::string("--MM-DD"), std::string("^--(\\d{1,2})-(\\d{1,2})$"))),
			// ---DDD
			std::make_pair(DatetimeType::eBaseType::gDay, std::make_pair(std::string("---DDD"), std::string("^---(\\d{1,3})$"))),
			// PnYnMnDTnHnMnS
			std::make_pair(DatetimeType::eBaseType::tDuration, std::make_pair(std::string("PnYnMnDTnHnMnS"), std::string("^P(-?\\d+)Y(-?\\d+)M(-?\\d+)DT(-?\\d+)H(-?\\d+)M(-?\\d+)S$")))
		};

		DatetimeType::DatetimeType(void)
			: DatetimeType("")
		{
		}

		DatetimeType::DatetimeType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
			ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
		}

		DatetimeType::DatetimeType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDatetimeType), ValueLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType)
		{
			ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
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
			ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Datetime::DatetimeDuration>::DefaultTranslator = std::bind(XSDString2Datetime, baseType, std::placeholders::_1);
		}

		SSUtils::Datetime::DatetimeDuration XSDString2Datetime(const DatetimeType::eBaseType type, const std::string & str)
		{
			const std::string &pattern(DatetimeType::Type2Pattern.find(type)->second.first);
			const std::string &regexPattern(DatetimeType::Type2Pattern.find(type)->second.second);
			if (!SSUtils::String::RegexChecker(regexPattern)(str))
			{
				std::cerr << str << "不是一个有效的" << DatetimeType::Type2String.find(type)->second << "类型（格式应为：" << pattern << "）" << std::endl;
				return SSUtils::Datetime::DatetimeDuration();
			}
			else
			{
				
				std::vector<std::string> parts(SSUtils::String::RegexCatcher(regexPattern)(str));
				switch (type)
				{
				case DatetimeType::eBaseType::tDate:
					return SSUtils::Datetime::DatetimeDuration(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), 0, 0, 0);
				case DatetimeType::eBaseType::tTime:
					return SSUtils::Datetime::DatetimeDuration(0, 0, 0, std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]));
				case DatetimeType::eBaseType::tDatetime:
					return SSUtils::Datetime::DatetimeDuration(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]), std::stoi(parts[4]), std::stoi(parts[5]), std::stoi(parts[6]));
				case DatetimeType::eBaseType::gYear:
					return SSUtils::Datetime::DatetimeDuration(std::stoi(parts[0]), 0, 0, 0, 0, 0);
				case DatetimeType::eBaseType::gYearMonth:
					return SSUtils::Datetime::DatetimeDuration(std::stoi(parts[0]), std::stoi(parts[1]), 0, 0, 0, 0);
				case DatetimeType::eBaseType::gMonth:
					return SSUtils::Datetime::DatetimeDuration(0, std::stoi(parts[0]), 0, 0, 0, 0);
				case DatetimeType::eBaseType::gMonthDay:
					return SSUtils::Datetime::DatetimeDuration(0, std::stoi(parts[0]), std::stoi(parts[1]), 0, 0, 0);
				case DatetimeType::eBaseType::gDay:
					return SSUtils::Datetime::DatetimeDuration(0, 0, std::stoi(parts[0]), 0, 0, 0);
				case DatetimeType::eBaseType::tDuration:
					return SSUtils::Datetime::DatetimeDuration(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]), std::stoi(parts[4]), std::stoi(parts[5]));
				default:
					return SSUtils::Datetime::DatetimeDuration();
				}
				return SSUtils::Datetime::DatetimeDuration();
			}
		}
	};
};
