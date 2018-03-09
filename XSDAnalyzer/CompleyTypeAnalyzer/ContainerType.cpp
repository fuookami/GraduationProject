#include "ContainerType.h"
#include "XSDToken.h"
#include "StringConvertUtils.h"
#include "StringUtils.h"

#include <boost/algorithm/string.hpp>

#include <iostream>

namespace XSDFrontend
{
	namespace SimpleType
	{
		ContainerType::ContainerType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		ContainerType::ContainerType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		const bool ContainerType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			static const std::string EmptyString("");
			static const std::map<eBaseType, std::string> ItemTypeAttrName =
			{
				std::make_pair(eBaseType::tList, Token::ListItemTypeAttr),
				std::make_pair(eBaseType::tUnion, Token::UnionItemTypeAttr)
			};

			std::string baseTypeNamesPrototype(node.getAttr(ItemTypeAttrName.find(m_baseType)->second));
			std::vector<std::string> baseTypeNames;

			boost::split(baseTypeNames, baseTypeNamesPrototype, boost::is_any_of(StringUtils::getSpaceChars()));
			m_baseTypeNames.insert(baseTypeNames.cbegin(), baseTypeNames.cend());

			return true;
		}
	};
};
