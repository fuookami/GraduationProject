#pragma once

#include "SimpleTypeInterface.h"

#include <map>
#include <set>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class SSXSDUtils_API_DECLSPEC StringType final : public ISimpleTypeInterface,
			public LengthLimitConfiguration, 
			public ValueEnumrationConfiguration<std::string>
		{
		public:
			enum class eBaseType
			{
				tQName,
				tString,
				tNormalizedString,
				tToken,
				tLanguage,
				tName,
				tNCName,
				tID,
				tIDRef,
				tIDRefs,
				tEntity,
				tEntities,
				tNMToken,
				tNMTokens,
				tAnyURI
			};
			static const int NoLengthValidator = -1;
			static const boost::bimap<std::string, StringType::eBaseType> String2Type;
			using ValueType = std::string;

		public:
			StringType(void);
			StringType(const std::string &name, const eBaseType baseType = eBaseType::tString);
			StringType(std::string &&name, const eBaseType baseType = eBaseType::tString);
			StringType(const StringType &ano) = default;
			StringType(StringType &&ano) = default;
			StringType &operator=(const StringType &rhs) = default;
			StringType &operator=(StringType &&rhs) = default;
			~StringType(void) = default;

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;
			std::shared_ptr<SSUtils::XML::Node> saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			inline void setPattern(const ValueType &pattern) { m_pattern = pattern; }
			inline void setPattern(const ValueType &&pattern) { m_pattern = std::move(m_pattern); }
			inline void removePattern(void) { m_pattern.clear(); }
			inline const ValueType &getPattern(void) const { return m_pattern; }

		private:
			eBaseType m_baseType;

			std::string m_pattern;
		};

		SSXSDUtils_API_DECLSPEC std::string XSDString2String(const std::string &str);
	};
};
