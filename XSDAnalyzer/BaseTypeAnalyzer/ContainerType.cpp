#include "ContainerType.h"
#include "XSDToken.h"
#include "StringConvertUtils.h"
#include "StringUtils.h"

#include <boost/algorithm/string.hpp>

#include <iostream>

namespace XSDAnalyzer
{
	namespace SimpleType
	{
		ContainerType::ContainerType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		ContainerType::ContainerType(const std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		ContainerType::ContainerType(const ContainerType & ano)
			: ISimpleTypeInterface(ano), m_baseType(ano.m_baseType), m_baseTypeNames(ano.m_baseTypeNames)
		{
		}

		ContainerType::ContainerType(const ContainerType && ano)
			: ISimpleTypeInterface(std::move(ano)), m_baseType(ano.m_baseType), m_baseTypeNames(std::move(ano.m_baseTypeNames))
		{
		}

		ContainerType & ContainerType::operator=(const ContainerType & rhs)
		{
			m_baseType = rhs.m_baseType;
			m_baseTypeNames = rhs.m_baseTypeNames;

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		ContainerType & ContainerType::operator=(const ContainerType && rhs)
		{
			m_baseType = rhs.m_baseType;
			m_baseTypeNames = std::move(rhs.m_baseTypeNames);

			ISimpleTypeInterface::operator=(rhs);

			return *this;
		}

		ContainerType::~ContainerType(void)
		{
		}

		void ContainerType::refreshValidator(const boost::property_tree::ptree & root)
		{
			static const std::string EmptyString("");
			static const std::map<eBaseType, std::string> ItemTypeAttrName = 
			{
				std::make_pair(eBaseType::tList, Token::ListItemTypeAttr),
				std::make_pair(eBaseType::tUnion, Token::UnionItemTypeAttr)
			};

			const auto &attrs(root.get_child(Token::AttrTag));
			std::string baseTypeNamesPrototype = StringConvertUtils::toLocal<StringConvertUtils::StringCodeId::UTF8>(attrs.get<std::string>(ItemTypeAttrName.find(m_baseType)->second, EmptyString));
			std::vector<std::string> baseTypeNames;

			boost::split(baseTypeNames, baseTypeNamesPrototype, boost::is_any_of(StringUtils::getSpaceChars()));
			m_baseTypeNames.insert(baseTypeNames.cbegin(), baseTypeNames.cend());
		}
	};
};
