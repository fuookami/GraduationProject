#include "ContainerType.h"
#include "XSDToken.h"
#include "StringUtils.h"

#include <boost/algorithm/string.hpp>

#include <iostream>

namespace XSDFrontend
{
	namespace SimpleType
	{
		const boost::bimap<std::string, ContainerType::eBaseType> ContainerType::String2ItemType = 
			[]()
		{
			typedef boost::bimap<std::string, ContainerType::eBaseType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(Token::ListItemTypeAttr, eBaseType::tList));
			ret.insert(pair_type(Token::UnionItemTypeAttr, eBaseType::tUnion));
			return ret;
		}();

		ContainerType::ContainerType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		ContainerType::ContainerType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tContainerType), m_baseType(baseType), m_baseTypeNames()
		{
		}

		const bool ContainerType::refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			static const std::string EmptyString("");

			std::string baseTypeNamesPrototype(node->getAttr(String2ItemType.right.find(m_baseType)->second));
			std::vector<std::string> baseTypeNames(SSUtils::String::split(baseTypeNamesPrototype, SSUtils::String::SpaceCharacters));
			m_baseTypeNames.insert(baseTypeNames.cbegin(), baseTypeNames.cend());

			return true;
		}

		std::set<std::string> ContainerType::neededTokens(void) const
		{
			return m_baseTypeNames;
		}
	};
};
