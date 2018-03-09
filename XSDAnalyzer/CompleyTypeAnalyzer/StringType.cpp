#include "StringType.h"
#include "StringUtils.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const ValueEnumrationConfiguration<std::string>::TranslateFunction ValueEnumrationConfiguration<std::string>::translator = XSDString2String;

		StringType::StringType(void)
			: StringType("")
		{
		}

		StringType::StringType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_pattern()
		{
		}

		StringType::StringType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType), m_pattern()
		{
		}

		const bool StringType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			if (!refreshLengthLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node);
			if (node.hasChild(XSDFrontend::Token::PatternTag))
			{
				const auto &patternNode(node.getChildren()[node.findChild(XSDFrontend::Token::PatternTag)]);
				if (patternNode.hasAttr(XSDFrontend::Token::ValueAttr))
				{
					m_pattern.assign(patternNode.getAttr(XSDFrontend::Token::ValueAttr));
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
