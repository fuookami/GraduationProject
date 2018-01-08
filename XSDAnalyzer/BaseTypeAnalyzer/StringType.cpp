#include "StringType.h"

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		StringType::StringType(void)
			: StringType("")
		{
		}

		StringType::StringType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tStringType), m_baseType(baseType), m_minLength(NoLengthValidator), m_maxLength(NoLengthValidator), m_pattern(), m_isEnum(), m_enumValues()
		{
		}

		StringType::StringType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tStringType), m_baseType(baseType), m_minLength(NoLengthValidator), m_maxLength(NoLengthValidator), m_pattern(), m_isEnum(), m_enumValues()
		{
		}

		StringType::StringType(const StringType & ano)
			: ISimpleTypeInterface(ano), m_baseType(ano.m_baseType), m_minLength(ano.m_minLength), m_maxLength(ano.m_maxLength), m_pattern(ano.m_pattern), m_isEnum(ano.m_isEnum), m_enumValues(ano.m_enumValues)
		{
		}

		StringType::StringType(const StringType && ano)
			: ISimpleTypeInterface(std::move(ano)), m_baseType(ano.m_baseType), m_minLength(ano.m_minLength), m_maxLength(ano.m_maxLength), m_pattern(ano.m_pattern), m_isEnum(ano.m_isEnum), m_enumValues(std::move(ano.m_enumValues))
		{
		}

		StringType & StringType::operator=(const StringType & rhs)
		{
			m_baseType = rhs.m_baseType;
			m_minLength = rhs.m_minLength;
			m_maxLength = rhs.m_maxLength;
			m_pattern = rhs.m_pattern;
			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		StringType & StringType::operator=(const StringType && rhs)
		{
			m_baseType = rhs.m_baseType;
			m_minLength = rhs.m_minLength;
			m_maxLength = rhs.m_maxLength;
			m_pattern = rhs.m_pattern;
			m_isEnum = rhs.m_isEnum;
			m_enumValues = std::move(rhs.m_enumValues);

			ISimpleTypeInterface::operator=(std::move(rhs));

			return *this;
		}

		StringType::~StringType(void)
		{
		}

		void StringType::refreshValidator(const boost::property_tree::ptree & root)
		{
			//! to do
		}
	};
};
