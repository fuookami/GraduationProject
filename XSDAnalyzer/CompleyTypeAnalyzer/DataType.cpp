#include "DataType.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		DataType::DataType(void)
			: DataType("")
		{
		}

		DataType::DataType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tDataType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
		}

		DataType::DataType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDataType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
		}

		DataType::DataType(const DataType & ano)
			: ISimpleTypeInterface(ano), LengthLimitConfiguration(ano), ValueEnumrationConfiguration(ano), 
			m_baseType(ano.m_baseType)
		{
		}

		DataType::DataType(const DataType && ano)
			: ISimpleTypeInterface(std::move(ano)), LengthLimitConfiguration(std::move(ano)), ValueEnumrationConfiguration(std::move(ano)), 
			m_baseType(ano.m_baseType)
		{
		}

		DataType & DataType::operator=(const DataType & rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(rhs);
			LengthLimitConfiguration::operator=(rhs);
			ValueEnumrationConfiguration::operator=(rhs);

			return *this;
		}

		DataType & DataType::operator=(const DataType && rhs)
		{
			m_baseType = rhs.m_baseType;

			ISimpleTypeInterface::operator=(std::move(rhs));
			LengthLimitConfiguration::operator=(std::move(rhs));
			ValueEnumrationConfiguration::operator=(std::move(rhs));

			return *this;
		}

		DataType::~DataType(void)
		{
		}

		void DataType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
