#pragma once

#include "SimpleTypeInterface.h"

#include <map>
#include <set>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		class StringType final : public ISimpleTypeInterface
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
			StringType(const std::string &&name, const eBaseType baseType = eBaseType::tString);
			StringType(const StringType &ano);
			StringType(const StringType &&ano);
			StringType &operator=(const StringType &rhs);
			StringType &operator=(const StringType &&rhs);
			~StringType(void);

			void refreshValidator(const boost::property_tree::ptree &root) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			inline void setLengthValidator(const int lenth) { m_minLength = m_maxLength = lenth; }
			inline void removeLengthValidator(void) { setLengthValidator(NoLengthValidator); }
			inline const int getLengthValidator(void) const { return m_minLength == m_maxLength ? m_minLength : NoLengthValidator; }

			inline void setMinLengthValidator(const int minLength) { m_minLength = minLength; }
			inline void removeMinLengthValidator(void) { setMinLengthValidator(NoLengthValidator); }
			inline const int getMinLengthValidator(void) const { return m_minLength; }

			inline void setMaxLengthValidator(const int maxLength) { m_maxLength = maxLength; }
			inline void removeMaxLengthValidator(void) { setMaxLengthValidator(NoLengthValidator); }
			inline const int getMaxLengthValidator(void) const { return m_maxLength; }

			inline void setPattern(const ValueType &pattern) { m_pattern = pattern; }
			inline void setPattern(const ValueType &&pattern) { m_pattern = std::move(m_pattern); }
			inline void removePattern(void) { m_pattern.clear(); }
			inline const ValueType &getPattern(void) const { return m_pattern; }

			inline void setIsEnum(const bool isEnum) { m_isEnum = isEnum; }
			inline const bool getIsEnum(void) const { return m_isEnum; }

			inline void addEnumValue(const ValueType &enumValue) { m_enumValues.insert(enumValue); }
			inline void addEnumValue(const ValueType &&enumValue) { m_enumValues.insert(std::move(enumValue)); }
			inline void eraseEnumValue(const ValueType &enumValue) { m_enumValues.erase(enumValue); }
			inline void clearEnumValue(void) { m_enumValues.clear(); }
			inline const bool hasEnumValue(const ValueType &enumValue) const { return m_enumValues.find(enumValue) != m_enumValues.cend(); }
			inline const std::set<ValueType> &getEnumValues(void) const { return m_enumValues; }

		private:
			eBaseType m_baseType;

			int m_minLength;
			int m_maxLength;
			std::string m_pattern;

			bool m_isEnum;
			std::set<ValueType> m_enumValues;
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
	};
};
