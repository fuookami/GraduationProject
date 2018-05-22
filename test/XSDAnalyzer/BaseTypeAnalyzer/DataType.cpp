#include "DataType.h"

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		const bool DataType::_ValueTypeCompare::operator()(const ValueType & lhs, const ValueType & rhs) const
		{
			for (ValueType::const_iterator lCurrIt(lhs.cbegin()), rCurrIt(rhs.cbegin()), lEdIt(lhs.cend()), rEdIt(rhs.cend()); lCurrIt != lEdIt && rCurrIt != rEdIt; ++lCurrIt, ++rCurrIt)
			{
				if (*lCurrIt < *rCurrIt)
				{
					return true;
				}
			}

			return false;
		}

		DataType::DataType(void)
			: DataType("")
		{
		}

		DataType::DataType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDataType), m_baseType(baseType), 
			m_maxLength(NoLengthValidator), m_minLength(NoLengthValidator), m_isEnum(false), m_enumValues()
		{
		}

		DataType::DataType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDataType), m_baseType(baseType),
			m_maxLength(NoLengthValidator), m_minLength(NoLengthValidator), m_isEnum(false), m_enumValues()
		{
		}

		DataType::DataType(const DataType & ano)
			: ISimpleTypeInterface(ano), m_baseType(ano.m_baseType),
			m_maxLength(ano.m_maxLength), m_minLength(ano.m_minLength), m_isEnum(ano.m_isEnum), m_enumValues(ano.m_enumValues)
		{
		}

		DataType::DataType(const DataType && ano)
			: ISimpleTypeInterface(std::move(ano)), m_baseType(ano.m_baseType),
			m_maxLength(ano.m_maxLength), m_minLength(ano.m_minLength), m_isEnum(ano.m_isEnum), m_enumValues(std::move(ano.m_enumValues))
		{
		}

		DataType & DataType::operator=(const DataType & rhs)
		{
			m_baseType = rhs.m_baseType;
			m_maxLength = rhs.m_maxLength;
			m_minLength = rhs.m_minLength;
			m_isEnum = rhs.m_isEnum;
			m_enumValues = rhs.m_enumValues;

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		DataType & DataType::operator=(const DataType && rhs)
		{
			m_baseType = rhs.m_baseType;
			m_maxLength = rhs.m_maxLength;
			m_minLength = rhs.m_minLength;
			m_isEnum = rhs.m_isEnum;
			m_enumValues = std::move(rhs.m_enumValues);

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		DataType::~DataType(void)
		{
		}

		void DataType::refreshValidator(const boost::property_tree::ptree & root)
		{
		}
	};
};
