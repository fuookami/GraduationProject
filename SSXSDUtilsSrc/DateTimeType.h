#pragma once

#include "SimpleTypeInterface.h"
#include "DatetimeUtils.h"

#include <map>
#include <set>
#include <memory>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class SSXSDUtils_API_DECLSPEC DatetimeType : public ISimpleTypeInterface,
			public ValueLimitConfiguration<SSUtils::Datetime::DatetimeDuration>,
			public ValueEnumrationConfiguration<SSUtils::Datetime::DatetimeDuration>
		{
		public:
			enum class eBaseType
			{
				tDate,
				tTime,
				tDatetime,
				gYear,
				gYearMonth,
				gMonth,
				gMonthDay,
				gDay,
				tDuration
			};
			static const boost::bimap<std::string, DatetimeType::eBaseType> String2Type;
			static const std::map<eBaseType, std::pair<std::string, std::string>> Type2Pattern;

		public:
			DatetimeType(void);
			DatetimeType(const std::string &name, const eBaseType baseType= eBaseType::tDatetime);
			DatetimeType(std::string &&name, const eBaseType baseType= eBaseType::tDatetime);
			DatetimeType(const DatetimeType &ano) = default;
			DatetimeType(DatetimeType &&ano) = default;
			DatetimeType &operator=(const DatetimeType &rhs) = default;
			DatetimeType &operator=(DatetimeType &&rhs) = default;
			~DatetimeType(void) = default;

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;
			std::shared_ptr<SSUtils::XML::Node> saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const override;

			void setBaseType(const eBaseType baseType);
			inline const eBaseType getBaseType(void) const { return m_baseType; }

		private:
			eBaseType m_baseType;
		};

		SSXSDUtils_API_DECLSPEC SSUtils::Datetime::DatetimeDuration XSDString2Datetime(const DatetimeType::eBaseType type, const std::string &str);
		SSXSDUtils_API_DECLSPEC std::string XSDDatetime2String(const DatetimeType::eBaseType type, const SSUtils::Datetime::DatetimeDuration &value);
	};
};
