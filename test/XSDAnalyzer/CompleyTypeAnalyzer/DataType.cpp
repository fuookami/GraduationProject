#include "DataType.h"
#include <functional>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const boost::bimap<std::string, DataType::eBaseType> DataType::String2Type =
			[]()
		{
			typedef boost::bimap<std::string, DataType::eBaseType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("hexBinary"), DataType::eBaseType::tHexBinary));
			ret.insert(pair_type(std::string("base64Binary"), DataType::eBaseType::tBase64Binary));
			return ret;
		}();

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

		std::shared_ptr<SSUtils::XML::Node> DataType::saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const
		{
			root->setAttr(XSDFrontend::Token::BaseTypeAttr, XSDFrontend::Token::XSNamespace + String2Type.right.find(m_baseType)->second);
			ISimpleTypeInterface::saveValidator(root);
			saveLengthLimitConfiguration(root);
			saveValueEnumrationConfiguration(root, std::bind(XSDData2String, m_baseType, std::placeholders::_1));
			
			return root;
		}

		void DataType::setBaseType(const eBaseType baseType)
		{
			m_baseType = baseType;
			DefaultTranslator = std::bind(XSDString2Data, baseType, std::placeholders::_1);
		}

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

		std::string XSDData2String(const DataType::eBaseType type, const SSUtils::Block & value)
		{
			switch (type)
			{
			case DataType::eBaseType::tBase64Binary:
				return SSUtils::Data::toBase64String(value);
			case DataType::eBaseType::tHexBinary:
				return SSUtils::Data::toHexString(value);
			case DataType::eBaseType::tRaw:
			default:
				return SSUtils::Data::toString(value);
			}
			return SSUtils::Data::toString(value);
		}
	};
};
