#pragma once

#include "SimpleTypeInterface.h"

#include <map>
#include <set>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class StringType final : public ISimpleTypeInterface, 
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

			const bool refreshValidator(const XMLUtils::XMLNode &node) override;

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

		static const std::map<std::string, StringType::eBaseType> StringBaseTypeName2Type =
		{
			std::make_pair(std::string("QName"), StringType::eBaseType::tQName),
			std::make_pair(std::string("string"), StringType::eBaseType::tString),
			std::make_pair(std::string("normalizedString"), StringType::eBaseType::tNormalizedString),
			std::make_pair(std::string("token"), StringType::eBaseType::tToken),
			std::make_pair(std::string("language"), StringType::eBaseType::tLanguage),
			std::make_pair(std::string("Name"), StringType::eBaseType::tName),
			std::make_pair(std::string("NCName"), StringType::eBaseType::tNCName),
			std::make_pair(std::string("ID"), StringType::eBaseType::tID),
			std::make_pair(std::string("IDREF"), StringType::eBaseType::tIDRef),
			std::make_pair(std::string("IDREFS"), StringType::eBaseType::tIDRefs),
			std::make_pair(std::string("Entity"), StringType::eBaseType::tEntity),
			std::make_pair(std::string("Entities"), StringType::eBaseType::tEntities),
			std::make_pair(std::string("NMTOKEN"), StringType::eBaseType::tNMToken),
			std::make_pair(std::string("NMTOKENS"), StringType::eBaseType::tNMTokens),
			std::make_pair(std::string("anyURI"), StringType::eBaseType::tAnyURI)
		};

		std::string XSDString2String(const std::string &str);
	};
};
