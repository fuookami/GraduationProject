#include "NumberType.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const NumberVariant ValueLimitConfiguration<NumberVariant>::NoValueValidator = NumberVariant();

		NumberType::NumberType(void)
			: NumberType("")
		{
		}

		NumberType::NumberType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		NumberType::NumberType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		NumberType::NumberType(const NumberType & ano)
			: ISimpleTypeInterface(ano), ValueLimitConfiguration(ano), ValueEnumrationConfiguration(ano), 
			m_baseType(ano.m_baseType), m_fractionDigits(ano.m_fractionDigits), m_totalDigits(ano.m_totalDigits)
		{
		}

		NumberType::NumberType(const NumberType && ano)
			: ISimpleTypeInterface(ano), ValueLimitConfiguration(std::move(ano)), ValueEnumrationConfiguration(std::move(ano)),
			m_baseType(ano.m_baseType), m_fractionDigits(ano.m_fractionDigits), m_totalDigits(ano.m_totalDigits)
		{
		}

		NumberType & NumberType::operator=(const NumberType & rhs)
		{
			m_baseType = rhs.m_baseType;

			m_fractionDigits = rhs.m_fractionDigits;
			m_totalDigits = rhs.m_totalDigits;

			ISimpleTypeInterface::operator=(rhs);
			ValueLimitConfiguration::operator=(rhs);
			ValueEnumrationConfiguration::operator=(rhs);

			return *this;
		}

		NumberType & NumberType::operator=(const NumberType && rhs)
		{
			m_baseType = rhs.m_baseType;

			m_fractionDigits = rhs.m_fractionDigits;
			m_totalDigits = rhs.m_totalDigits;

			ISimpleTypeInterface::operator=(std::move(rhs));
			ValueLimitConfiguration::operator=(std::move(rhs));
			ValueEnumrationConfiguration::operator=(std::move(rhs));

			return *this;
		}

		NumberType::~NumberType(void)
		{
		}

		void NumberType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
