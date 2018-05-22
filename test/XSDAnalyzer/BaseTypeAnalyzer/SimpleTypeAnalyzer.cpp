#include "SimpleTypeAnalyzer.h"
#include "XSDToken.h"
#include "StringConvertUtils.h"

#include <boost/algorithm/string.hpp>

#include <exception>

namespace XSDAnalyzer
{
	SimpleTypeAnalyzer::SimpleTypeAnalyzer(void)
		: m_stringTypes(), m_numberTypes(), m_dateTimeTypes(), m_dataTypes(), m_simpleTypes()
	{
	}

	SimpleTypeAnalyzer::~SimpleTypeAnalyzer(void)
	{
	}

	const std::string SimpleTypeAnalyzer::scan(const boost::property_tree::ptree & pt)
	{
		static const std::string EmptyString("");
		
		std::string typeName;

		for (const auto &node : pt)
		{
			if (node.first == Token::AttrTag)
			{
				typeName = StringConvertUtils::toLocal<StringConvertUtils::StringCodeId::UTF8>(node.second.get<std::string>(Token::NameAttr, EmptyString));
				// ��������Ѿ����ڣ��򷵻ؿ��ַ����������������ⲻ��
				if (isTypeExist(typeName))
				{
					return EmptyString;
				}
				// ���������Ϊ�գ����Ĭ��������������һ���µ�
				if (typeName.empty())
				{
					do
					{
						typeName = getNewDefaultName();
					} while (isTypeExist(typeName));
				}
			}
			else if (node.first == Token::TypeTag)
			{
				if (!analyseType(typeName, node.second))
				{
					return EmptyString;
				}
			}
			else if (node.first == Token::ListTag)
			{
				if (!checkAndInsertType(m_containerTypes, SimpleType::ContainerType::eBaseType::tList, typeName, "", node.second))
				{
					return EmptyString;
				}
				checkAndEraseIlegalTypeInContainer(m_containerTypes.find(typeName)->second);
			}
			else if (node.first == Token::UnionTag)
			{
				if (!checkAndInsertType(m_containerTypes, SimpleType::ContainerType::eBaseType::tUnion, typeName, "", node.second))
				{
					return EmptyString;
				}
				checkAndEraseIlegalTypeInContainer(m_containerTypes.find(typeName)->second);
			}
		}

		return typeName;
	}

	const SimpleType::eSimpleType SimpleTypeAnalyzer::getType(const std::string &typeName) const
	{
		auto it(m_simpleTypes.find(typeName));

		if (it != m_simpleTypes.cend())
		{
			return it->second->type();
		}
		else
		{
			return SimpleType::eSimpleType::tNonExist;
		}
	}

	const std::shared_ptr<SimpleType::StringType> SimpleTypeAnalyzer::getStringType(const std::string & typeName) const
	{
		return getType(typeName, m_stringTypes);
	}

	const std::shared_ptr<SimpleType::NumberType> SimpleTypeAnalyzer::getNumberType(const std::string & typeName) const
	{
		return getType(typeName, m_numberTypes);
	}

	const std::shared_ptr<SimpleType::DateTimeType> SimpleTypeAnalyzer::getDateTimeType(const std::string & typeName) const
	{
		return getType(typeName, m_dateTimeTypes);
	}

	const std::shared_ptr<SimpleType::DataType> SimpleTypeAnalyzer::getDataType(const std::string & typeName) const
	{
		return getType(typeName, m_dataTypes);
	}

	const std::shared_ptr<SimpleType::ContainerType> SimpleTypeAnalyzer::getContainerType(const std::string & typeName) const
	{
		return getType(typeName, m_containerTypes);
	}

	const std::string SimpleTypeAnalyzer::getNewDefaultName(void)
	{
		unsigned int defaultNameNumber(0);
		static const std::string SimpleTypeNamePrefix("simple_type_");
		
		++defaultNameNumber;
		return SimpleTypeNamePrefix + std::to_string(defaultNameNumber);
	}

	const bool SimpleTypeAnalyzer::analyseType(const std::string & typeName, const boost::property_tree::ptree & typeRoot)
	{
		static const std::string EmptyString("");

		const auto &typeAttrNode(typeRoot.get_child(Token::AttrTag));
		const std::string baseTypeName(StringConvertUtils::toLocal<StringConvertUtils::StringCodeId::UTF8>(typeAttrNode.get<std::string>(Token::BaseTypeAttr, EmptyString)));

		// ����Ƿ���ԭ�����ͣ�����Ƿ���xs����xsd��ͷ��
		if (Token::isInXSDNameSpace(baseTypeName))
		{
			/* ����ǣ����ڸ���������ʱ���Ѱ��������
			* �������һ���ҵ��ˣ��򴴽�һ����Ӧ��������
			* ���û���ҵ������׳��쳣
			*/
			std::vector<std::string> baseTypeParts;
			boost::split(baseTypeParts, baseTypeName, boost::is_any_of(Token::NamespaceSeparator));

			if (baseTypeParts.size() == 2)
			{
				// ��һ���ǲ���ԭ������
				if (checkAndInsertType(m_stringTypes, SimpleType::StringBaseTypeName2Type, typeName, baseTypeParts.back(), typeRoot)
					|| checkAndInsertType(m_numberTypes, SimpleType::NumberBaseTypeName2Type, typeName, baseTypeParts.back(), typeRoot)
					|| checkAndInsertType(m_dateTimeTypes, SimpleType::DateTimeBaseTypeName2Type, typeName, baseTypeParts.back(), typeRoot)
					|| checkAndInsertType(m_dataTypes, SimpleType::DataBaseTypeName2Type, typeName, baseTypeParts.back(), typeRoot)
					)
				{
					return true;
				}
				else
				{
					static const std::string ErrorPrefix("δ�����ԭ�����ͣ�");
					throw std::logic_error(ErrorPrefix + baseTypeName);
				}
			}
			else
			{
				static const std::string ErrorPrefix("�����ԭ�����ͣ�");
				throw std::logic_error(ErrorPrefix + baseTypeName);
			}
		}
		else
		{
			/* ����񣬼���Ƿ��Ѿ��ڴʱ���
			* ����ڣ���������Ӧ�����ͣ���������������
			* ������ڣ��׳��쳣
			*/
			if (isTypeExist(baseTypeName))
			{
				const SimpleType::ISimpleTypeInterface *prototypeSimpleType(m_simpleTypes.find(baseTypeName)->second);

				switch (prototypeSimpleType->type())
				{
				case SimpleType::eSimpleType::tStringType:
					return checkAndInsertType(m_stringTypes, prototypeSimpleType, typeName, typeRoot);
					break;
				case SimpleType::eSimpleType::tNumberType:
					return checkAndInsertType(m_numberTypes, prototypeSimpleType, typeName, typeRoot);
					break;
				case SimpleType::eSimpleType::tDateTimeType:
					return checkAndInsertType(m_dateTimeTypes, prototypeSimpleType, typeName, typeRoot);
					break;
				case SimpleType::eSimpleType::tDataType:
					return checkAndInsertType(m_dataTypes, prototypeSimpleType, typeName, typeRoot);
				case SimpleType::eSimpleType::tContainerType:
				{
					static const std::string ErrorPrefix("���������������ͣ�Union��List����������������������");
					throw std::logic_error(ErrorPrefix + baseTypeName);
				}
					break;
				case SimpleType::eSimpleType::tNonExist: 
				default:
					return false;
					break;
				}
				return false;
			}
			else
			{
				static const std::string ErrorPrefix("δ������û����ͣ�");
				throw std::logic_error(ErrorPrefix + baseTypeName);
			}
		}
	}
	void SimpleTypeAnalyzer::checkAndEraseIlegalTypeInContainer(std::shared_ptr<SimpleType::ContainerType> type)
	{
		std::vector<std::string> ilegalTypeNames;
		for (const std::string &typeName : type->getBaseTypes())
		{
			if (!isTypeExist(typeName))
			{
				ilegalTypeNames.push_back(typeName);
			}
		}

		for (const std::string &ilegalTypeName : ilegalTypeNames)
		{
			type->eraseBaseType(ilegalTypeName);
		}
	}
};
 