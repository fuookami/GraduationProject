#pragma once

#include "SimpleTypeInterface.h"
#include "NumberVariant.h"

#include <map>
#include <set>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		class NumberType final : public ISimpleTypeInterface
		{
		public:
			enum class eBaseType
			{
				tFloat,
				tDouble,
				tDecimal,
				tInteger,
				tNonPositiveInteger,
				tNegativeInteger,
				tLong,
				tInt,
				tShort,
				tByte,
				tNonNegativeInteger,
				tPositiveInteger,
				tUnsignedLong,
				tUnsignedInt,
				tUnsignedShort,
				tUnsignedByte
			};
			static const int NoDigitValidator = -1;
			using ValueType = NumberVariant;

		public:
			NumberType(void);
			NumberType(const std::string &name, const eBaseType baseType = eBaseType::tDouble);
			NumberType(const std::string &&name, const eBaseType baseType = eBaseType::tDouble);
			NumberType(const NumberType &ano);
			NumberType(const NumberType &&ano);
			NumberType &operator=(const NumberType &rhs);
			NumberType &operator=(const NumberType &&rhs);
			~NumberType(void);

			void refreshValidator(const boost::property_tree::ptree &root) override;

			inline void setBaseType(const eBaseType baseType) { m_baseType = baseType; }
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			inline void setFractionDigits(const int fractionDigits) { m_fractionDigits = fractionDigits; }
			inline void refreshFractionDigits(void) { setFractionDigits(NoDigitValidator); }
			inline const int getFractionDigits(void) const { return m_fractionDigits; }

			void setMaxExclusive(const ValueType &maxExclusive);
			void setMaxExclusive(const ValueType &&maxExclusive);
			inline void removeMaxExclusive(void) { m_maxExclusive.clear(); }
			inline const bool hasMaxExclusive(void) { return !m_maxExclusive.empty(); }
			inline const ValueType &getMaxExclusive(void) { return m_maxExclusive; }

			void setMaxInclusive(const ValueType &maxInclusive);
			void setMaxInclusive(const ValueType &&maxInclusive);
			inline void removeMaxInclusive(void) { m_maxInclusive.clear(); }
			inline const bool hasMaxInclusive(void) { return !m_maxInclusive.empty(); }
			inline const ValueType &getMaxInclusive(void) { return m_maxInclusive; }

			void setMinExclusive(const ValueType &minExclusive);
			void setMinExclusive(const ValueType &&minExclusive);
			inline void removeMinExclusive(void) { m_minExclusive.clear(); }
			inline const bool hasMinExclusive(void) { return !m_minExclusive.empty(); }
			inline const ValueType &getMinExclusive(void) { return m_minExclusive; }

			void setMinInclusive(const ValueType &minInclusive);
			void setMinInclusive(const ValueType &&minInclusive);
			inline void removeMinInclusive(void) { m_minInclusive.clear(); }
			inline const bool hasMinInclusive(void) { return !m_minInclusive.empty(); }
			inline const ValueType &getMinInclusive(void) { return m_minInclusive; }

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

			int m_fractionDigits;
			int m_totalDigits;

			ValueType m_maxExclusive;
			ValueType m_maxInclusive;

			ValueType m_minExclusive;
			ValueType m_minInclusive;

			bool m_isEnum;
			std::set<ValueType> m_enumValues;
		};

		static const std::map<std::string, NumberType::eBaseType> NumberBaseTypeName2Type = 
		{
			std::make_pair(std::string("float"), NumberType::eBaseType::tFloat),
			std::make_pair(std::string("double"), NumberType::eBaseType::tDouble),
			std::make_pair(std::string("decimal"), NumberType::eBaseType::tDecimal),
			std::make_pair(std::string("integer"), NumberType::eBaseType::tInteger),
			std::make_pair(std::string("nonPositiveInteger"), NumberType::eBaseType::tNonPositiveInteger),
			std::make_pair(std::string("negativeInteger"), NumberType::eBaseType::tNegativeInteger),
			std::make_pair(std::string("long"), NumberType::eBaseType::tLong),
			std::make_pair(std::string("int"), NumberType::eBaseType::tInt),
			std::make_pair(std::string("short"), NumberType::eBaseType::tShort),
			std::make_pair(std::string("byte"), NumberType::eBaseType::tByte),
			std::make_pair(std::string("nonNegativeInteger"), NumberType::eBaseType::tNonNegativeInteger),
			std::make_pair(std::string("positiveInteger"), NumberType::eBaseType::tPositiveInteger),
			std::make_pair(std::string("unsignedLong"), NumberType::eBaseType::tUnsignedLong),
			std::make_pair(std::string("unsignedInt"), NumberType::eBaseType::tUnsignedInt),
			std::make_pair(std::string("unsignedShort"), NumberType::eBaseType::tUnsignedShort),
			std::make_pair(std::string("unsignedBytes"), NumberType::eBaseType::tUnsignedByte)
		};
	}
};
