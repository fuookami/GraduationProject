#include "NumberType.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const NumberVariant ValueLimitConfiguration<NumberVariant>::NoValueValidator = NumberVariant();

		const ValueLimitConfiguration<NumberVariant>::TranslateFunction ValueLimitConfiguration<NumberVariant>::translator = XSDString2NumberVairant;
		const ValueEnumrationConfiguration<NumberVariant>::TranslateFunction ValueEnumrationConfiguration<NumberVariant>::translator = XSDString2NumberVairant;

		NumberType::NumberType(void)
			: NumberType("")
		{
		}

		NumberType::NumberType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		NumberType::NumberType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		void NumberType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}

		NumberVariant XSDString2NumberVairant(const std::string & str)
		{
			//! to do
			return NumberVariant();
		}
	};
};
