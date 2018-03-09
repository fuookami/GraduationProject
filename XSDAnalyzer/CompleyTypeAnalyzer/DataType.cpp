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

		DataType::DataType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDataType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
		}

		const bool DataType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			if (!refreshLengthLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node);

			return true;
		}
	};
};
