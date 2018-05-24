#include "stdafx.h"
#include "StringType.h"
#include "SSUtils\StringUtils.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const boost::bimap<std::string, StringType::eBaseType> StringType::String2Type =
			[]()
		{
			typedef boost::bimap<std::string, StringType::eBaseType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("QName"), StringType::eBaseType::tQName));
			ret.insert(pair_type(std::string("string"), StringType::eBaseType::tString));
			ret.insert(pair_type(std::string("normalizedString"), StringType::eBaseType::tNormalizedString));
			ret.insert(pair_type(std::string("token"), StringType::eBaseType::tToken));
			ret.insert(pair_type(std::string("language"), StringType::eBaseType::tLanguage));
			ret.insert(pair_type(std::string("Name"), StringType::eBaseType::tName));
			ret.insert(pair_type(std::string("NCName"), StringType::eBaseType::tNCName));
			ret.insert(pair_type(std::string("ID"), StringType::eBaseType::tID));
			ret.insert(pair_type(std::string("IDREF"), StringType::eBaseType::tIDRef));
			ret.insert(pair_type(std::string("IDREFS"), StringType::eBaseType::tIDRefs));
			ret.insert(pair_type(std::string("Entity"), StringType::eBaseType::tEntity));
			ret.insert(pair_type(std::string("Entities"), StringType::eBaseType::tEntities));
			ret.insert(pair_type(std::string("NMTOKEN"), StringType::eBaseType::tNMToken));
			ret.insert(pair_type(std::string("NMTOKENS"), StringType::eBaseType::tNMTokens));
			ret.insert(pair_type(std::string("anyURI"), StringType::eBaseType::tAnyURI));
			return ret;
		}();

		StringType::StringType(void)
			: StringType("")
		{
		}

		StringType::StringType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_pattern()
		{
			DefaultTranslator = XSDString2String;
		}

		StringType::StringType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType), m_pattern()
		{
			DefaultTranslator = XSDString2String;
		}

		const bool StringType::refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			if (!refreshLengthLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node);
			if (node->hasChild(XSDFrontend::Token::PatternTag()))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::PatternTag())]);
				if (child != nullptr && child->hasAttr(XSDFrontend::Token::ValueAttr()))
				{
					m_pattern.assign(child->getAttr(XSDFrontend::Token::ValueAttr()));
				}
			}

			return true;
		}

		std::shared_ptr<SSUtils::XML::Node> StringType::saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const
		{
			root->setAttr(XSDFrontend::Token::BaseTypeAttr(), XSDFrontend::Token::XSNamespace() + String2Type.right.find(m_baseType)->second);
			ISimpleTypeInterface::saveValidator(root);
			if (!m_pattern.empty())
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::PatternTag()));
				node->setAttr(XSDFrontend::Token::ValueAttr(), m_pattern);
				root->addChild(node);
			}
			saveLengthLimitConfiguration(root);
			saveValueEnumrationConfiguration(root);

			return root;
		}

		std::string XSDString2String(const std::string & str)
		{
			return str;
		}
	};
};
