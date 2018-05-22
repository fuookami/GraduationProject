#include "DateTimeType.h"

#include <cstdint>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		const DateTimeType::ValueType DateTimeType::NoValueValidator = DateTimeType::ValueType(INT16_MIN, static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));

		DateTimeType::DateTime::DateTime(void)
			: enabled(false), value(NoValueValidator)
		{
		}

		DateTimeType::DateTime::DateTime(const DateTime &ano)
			: enabled(ano.enabled), value(ano.value)
		{
		}

		DateTimeType::DateTime::DateTime(const DateTime &&ano)
			: enabled(ano.enabled), value(std::move(ano.value))
		{
		}

		DateTimeType::DateTime &DateTimeType::DateTime::operator=(const DateTime &rhs)
		{
			enabled = rhs.enabled;
			value = rhs.value;

			return *this;
		}

		DateTimeType::DateTime &DateTimeType::DateTime::operator=(const DateTime &&rhs)
		{
			enabled = rhs.enabled;
			value = std::move(rhs.value);

			return *this;
		}

		DateTimeType::DateTime::~DateTime(void)
		{
		}

		void DateTimeType::DateTime::set(const ValueType &_value)
		{
			enabled = true;
			value = _value;
		}

		void DateTimeType::DateTime::set(const ValueType &&_value)
		{
			enabled = true;
			value = std::move(_value);
		}

		void DateTimeType::DateTime::clear(void)
		{
			enabled = false;
			value = NoValueValidator;
		}

		const bool DateTimeType::_ValueTypeCompare::operator()(const ValueType & lhs, const ValueType & rhs) const
		{
			return lhs < rhs;
		}

		DateTimeType::DateTimeType(void)
			: DateTimeType("")
		{
		}

		DateTimeType::DateTimeType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDateTimeType), m_baseType(baseType), 
			m_maxExclusive(), m_maxInclusive(), m_minExclusive(), m_minInclusive(), 
			m_isEnum(false), m_enumValues()
		{
		}

		DateTimeType::DateTimeType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDateTimeType), m_baseType(baseType), 
			m_maxExclusive(), m_maxInclusive(), m_minExclusive(), m_minInclusive(), 
			m_isEnum(false), m_enumValues()
		{
		}

		DateTimeType::DateTimeType(const DateTimeType & ano)
			: ISimpleTypeInterface(ano), m_baseType(ano.m_baseType), 
			m_minExclusive(ano.m_minExclusive), m_minInclusive(ano.m_minInclusive), m_maxExclusive(ano.m_maxExclusive), m_maxInclusive(ano.m_maxInclusive), 
			m_isEnum(ano.m_isEnum), m_enumValues(ano.m_enumValues)
		{
		}

		DateTimeType::DateTimeType(const DateTimeType && ano)
			: ISimpleTypeInterface(std::move(ano)), m_baseType(ano.m_baseType), 
			m_minExclusive(ano.m_minExclusive), m_minInclusive(ano.m_minInclusive), m_maxExclusive(ano.m_maxExclusive), m_maxInclusive(ano.m_maxInclusive), 
			m_isEnum(ano.m_isEnum), m_enumValues(std::move(ano.m_enumValues))
		{
		}

		DateTimeType & DateTimeType::operator=(const DateTimeType & rhs)
		{
			m_baseType = rhs.m_baseType;

			m_minExclusive = rhs.m_minExclusive;
			m_minInclusive = rhs.m_minInclusive;
			m_maxExclusive = rhs.m_maxExclusive;
			m_maxInclusive = rhs.m_maxInclusive;

			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		DateTimeType & DateTimeType::operator=(const DateTimeType && rhs)
		{
			m_baseType = rhs.m_baseType;

			m_minExclusive = std::move(rhs.m_minExclusive);
			m_minInclusive = std::move(rhs.m_minInclusive);
			m_maxExclusive = std::move(rhs.m_maxExclusive);
			m_maxInclusive = std::move(rhs.m_maxInclusive);

			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			ISimpleTypeInterface::operator=(std::move(rhs));

			return *this;
		}

		DateTimeType::~DateTimeType(void)
		{
		}

		void DateTimeType::refreshValidator(const boost::property_tree::ptree & root)
		{
			//! to do
		}

		void DateTimeType::setMaxExclusive(const ValueType & maxExclusive)
		{
			m_maxExclusive.set(maxExclusive);
			m_maxInclusive.clear();
		}

		void DateTimeType::setMaxExclusive(const ValueType && maxExclusive)
		{
			m_maxExclusive.set(std::move(maxExclusive));
			m_maxInclusive.clear();
		}

		void DateTimeType::setMaxInclusive(const ValueType & maxInclusive)
		{
			m_maxInclusive.set(maxInclusive);
			m_maxExclusive.clear();
		}

		void DateTimeType::setMaxInclusive(const ValueType && maxInclusive)
		{
			m_maxInclusive.set(std::move(maxInclusive));
			m_maxExclusive.clear();
		}

		void DateTimeType::setMinExclusive(const ValueType & minExclusive)
		{
			m_minExclusive.set(minExclusive);
			m_minInclusive.clear();
		}

		void DateTimeType::setMinExclusive(const ValueType && minExclusive)
		{
			m_minExclusive.set(std::move(minExclusive));
			m_minInclusive.clear();
		}

		void DateTimeType::setMinInclusive(const ValueType & minInclusive)
		{
			m_minInclusive.set(minInclusive);
			m_minExclusive.clear();
		}

		void DateTimeType::setMinInclusive(const ValueType && minInclusive)
		{
			m_minInclusive.set(std::move(minInclusive));
			m_minExclusive.clear();
		}
	};
};
