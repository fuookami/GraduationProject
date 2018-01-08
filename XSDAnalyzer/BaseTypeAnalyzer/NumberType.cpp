#include "NumberType.h"

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		NumberType::NumberType(void)
			: NumberType("")
		{
		}

		NumberType::NumberType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tNumberType), m_baseType(baseType), 
			m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator),
			m_minExclusive(), m_minInclusive(), m_maxExclusive(), m_maxInclusive(), 
			m_isEnum(false), m_enumValues()
		{
		}

		NumberType::NumberType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tNumberType), m_baseType(baseType), 
			m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator),
			m_minExclusive(), m_minInclusive(), m_maxExclusive(), m_maxInclusive(), 
			m_isEnum(false), m_enumValues()
		{
		}

		NumberType::NumberType(const NumberType & ano)
			: ISimpleTypeInterface(ano), m_baseType(ano.m_baseType), 
			m_fractionDigits(ano.m_fractionDigits), m_totalDigits(ano.m_totalDigits), 
			m_minExclusive(ano.m_minExclusive), m_minInclusive(ano.m_minInclusive), m_maxExclusive(ano.m_maxExclusive), m_maxInclusive(ano.m_maxInclusive), 
			m_isEnum(ano.m_isEnum), m_enumValues(ano.m_enumValues)
		{
		}

		NumberType::NumberType(const NumberType && ano)
			: ISimpleTypeInterface(std::move(ano)), m_baseType(ano.m_baseType), 
			m_fractionDigits(ano.m_fractionDigits), m_totalDigits(ano.m_totalDigits), 
			m_minExclusive(ano.m_minExclusive), m_minInclusive(ano.m_minInclusive), m_maxExclusive(ano.m_maxExclusive), m_maxInclusive(ano.m_maxInclusive), 
			m_isEnum(ano.m_isEnum), m_enumValues(std::move(ano.m_enumValues))
		{
		}

		NumberType & NumberType::operator=(const NumberType & rhs)
		{
			m_baseType = rhs.m_baseType;

			m_fractionDigits = rhs.m_fractionDigits;
			m_totalDigits = rhs.m_totalDigits;

			m_minExclusive = rhs.m_minExclusive;
			m_minInclusive = rhs.m_minInclusive;
			m_maxExclusive = rhs.m_maxExclusive;
			m_maxInclusive = rhs.m_maxInclusive;

			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			ISimpleTypeInterface::operator=(rhs);
			
			return *this;
		}

		NumberType & NumberType::operator=(const NumberType && rhs)
		{
			m_baseType = rhs.m_baseType;

			m_fractionDigits = rhs.m_fractionDigits;
			m_totalDigits = rhs.m_totalDigits;
			
			m_minExclusive = std::move(rhs.m_minExclusive);
			m_minInclusive = std::move(rhs.m_minInclusive);
			m_maxExclusive = std::move(rhs.m_maxExclusive);
			m_maxInclusive = std::move(rhs.m_maxInclusive);

			m_isEnum = rhs.m_isEnum;
			m_enumValues = std::move(rhs.m_enumValues);

			ISimpleTypeInterface::operator=(std::move(rhs));

			return *this;
		}

		NumberType::~NumberType(void)
		{
		}

		void NumberType::refreshValidator(const boost::property_tree::ptree & root)
		{
			//! to do
		}

		void NumberType::setMaxExclusive(const ValueType &maxExclusive)
		{
			m_maxExclusive = maxExclusive;
			m_maxInclusive.clear();
		}

		void NumberType::setMaxExclusive(const ValueType &&maxExclusive)
		{
			m_maxExclusive = std::move(maxExclusive);
			m_maxInclusive.clear();
		}

		void NumberType::setMaxInclusive(const ValueType &maxInclusive)
		{
			m_maxInclusive = maxInclusive;
			m_maxExclusive.clear();
		}

		void NumberType::setMaxInclusive(const ValueType &&maxInclusive)
		{
			m_maxInclusive = std::move(maxInclusive);
			m_maxExclusive.clear();
		}

		void NumberType::setMinExclusive(const ValueType &minExclusive)
		{
			m_minExclusive = minExclusive;
			m_minInclusive.clear();
		}

		void NumberType::setMinExclusive(const ValueType &&minExclusive)
		{
			m_minExclusive = std::move(minExclusive);
			m_minInclusive.clear();
		}

		void NumberType::setMinInclusive(const ValueType &minInclusive)
		{
			m_minInclusive = minInclusive;
			m_minInclusive.clear();
		}

		void NumberType::setMinInclusive(const ValueType &&minInclusive)
		{
			m_minInclusive = std::move(minInclusive);
			m_minInclusive.clear();
		}
	};
};
