#pragma once

#include "SimpleTypeInterface.h"
#include "MathUtils.h"
#include "SimpleTypeValueLimitConfiguration.h"
#include "SimpleTypeValueEnumrationConfiguration.h"

#include <map>
#include <set>

namespace XSDFrontend
{
	namespace SimpleType
	{
		class NumberType final : public ISimpleTypeInterface, 
			public ValueLimitConfiguration<SSUtils::Math::Real>, 
			public ValueEnumrationConfiguration<SSUtils::Math::Real>
		{
		public:
			enum class eBaseType
			{
				tBoolean,
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

		public:
			NumberType(void);
			NumberType(const std::string &name, const eBaseType baseType = eBaseType::tDouble);
			NumberType(std::string &&name, const eBaseType baseType = eBaseType::tDouble);
			NumberType(const NumberType &ano) = default;
			NumberType(NumberType &&ano) = default;
			NumberType &operator=(const NumberType &rhs) = default;
			NumberType &operator=(NumberType &&rhs) = default;
			~NumberType(void) = default;

			const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) override;

			void setBaseType(const eBaseType baseType);
			inline const eBaseType getBaseType(void) const { return m_baseType; }

			inline void setFractionDigits(const int fractionDigits) { m_fractionDigits = fractionDigits; }
			inline void removeFractionDigits(void) { setFractionDigits(NoDigitValidator); }
			inline const int getFractionDigits(void) const { return m_fractionDigits; }

			inline void setTotalDigits(const int totalDigits) { m_totalDigits = totalDigits; }
			inline void removeTotalDigits(void) { setTotalDigits(NoDigitValidator); }
			inline const int getTotalDigits(void)const { return m_totalDigits; }

		private:
			eBaseType m_baseType;

			int m_fractionDigits;
			int m_totalDigits;
		};

		extern const std::map<std::string, NumberType::eBaseType> NumberBaseTypeName2Type;

		SSUtils::Math::Real XSDString2NumberVairant(const NumberType::eBaseType type, const std::string &str);
	}
};
