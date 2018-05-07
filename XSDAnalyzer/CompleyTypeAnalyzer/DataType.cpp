#include "DataType.h"
#include <functional>

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
			DefaultTranslator = std::bind(XSDString2Data, baseType, std::placeholders::_1);
		}

		DataType::DataType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tDataType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType)
		{
			DefaultTranslator = std::bind(XSDString2Data, baseType, std::placeholders::_1);
		}

		const bool DataType::refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			if (!refreshLengthLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node, std::bind(XSDString2Data, m_baseType, std::placeholders::_1));

			return true;
		}

		void DataType::setBaseType(const eBaseType baseType)
		{
			m_baseType = baseType;
			DefaultTranslator = std::bind(XSDString2Data, baseType, std::placeholders::_1);
		}

		const std::map<std::string, DataType::eBaseType> DataBaseTypeName2Type =
		{
			std::make_pair(std::string("hexBinary"), DataType::eBaseType::tHexBinary),
			std::make_pair(std::string("base64Binary"), DataType::eBaseType::tBase64Binary)
		};

		SSUtils::Block XSDString2Data(const DataType::eBaseType type, const std::string & str)
		{
			switch (type)
			{
			case DataType::eBaseType::tRaw:
				return SSUtils::Data::fromString(str);
			case DataType::eBaseType::tBase64Binary:
				return SSUtils::Data::fromBase64String(str);
			case DataType::eBaseType::tHexBinary:
				return SSUtils::Data::fromHexString(str);
			default:
				return SSUtils::Data::fromString(str);
			}
			return SSUtils::Data::fromString(str);
		}
	};
};
