#include "StringType.h"
#include "StringUtils.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const std::map<std::string, StringType::eBaseType> StringType::String2Type =
		{
			std::make_pair(std::string("QName"), StringType::eBaseType::tQName),
			std::make_pair(std::string("string"), StringType::eBaseType::tString),
			std::make_pair(std::string("normalizedString"), StringType::eBaseType::tNormalizedString),
			std::make_pair(std::string("token"), StringType::eBaseType::tToken),
			std::make_pair(std::string("language"), StringType::eBaseType::tLanguage),
			std::make_pair(std::string("Name"), StringType::eBaseType::tName),
			std::make_pair(std::string("NCName"), StringType::eBaseType::tNCName),
			std::make_pair(std::string("ID"), StringType::eBaseType::tID),
			std::make_pair(std::string("IDREF"), StringType::eBaseType::tIDRef),
			std::make_pair(std::string("IDREFS"), StringType::eBaseType::tIDRefs),
			std::make_pair(std::string("Entity"), StringType::eBaseType::tEntity),
			std::make_pair(std::string("Entities"), StringType::eBaseType::tEntities),
			std::make_pair(std::string("NMTOKEN"), StringType::eBaseType::tNMToken),
			std::make_pair(std::string("NMTOKENS"), StringType::eBaseType::tNMTokens),
			std::make_pair(std::string("anyURI"), StringType::eBaseType::tAnyURI)
		};

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
			if (node->hasChild(XSDFrontend::Token::PatternTag))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::PatternTag)]);
				if (child != nullptr && child->hasAttr(XSDFrontend::Token::ValueAttr))
				{
					m_pattern.assign(child->getAttr(XSDFrontend::Token::ValueAttr));
				}
			}

			return true;
		}

		std::string XSDString2String(const std::string & str)
		{
			return str;
		}
	};
};
