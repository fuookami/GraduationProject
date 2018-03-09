#include "NumberType.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const NumberVariant ValueLimitConfiguration<NumberVariant>::NoValueValidator = NumberVariant();

		const ValueLimitConfiguration<NumberVariant>::TranslateFunction ValueLimitConfiguration<NumberVariant>::translator = XSDString2NumberVairant;
		const ValueEnumrationConfiguration<NumberVariant>::TranslateFunction ValueEnumrationConfiguration<NumberVariant>::translator = XSDString2NumberVairant;

		NumberType::NumberType(void)
			: NumberType("")
		{
		}

		NumberType::NumberType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		NumberType::NumberType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
		}

		const bool NumberType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			if (!refreshValueLimitConfiguration(node))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node);

			if (node.hasChild(XSDFrontend::Token::FractionDigitsTag))
			{
				const auto &fractionDigitNode(node.getChildren()[node.findChild(XSDFrontend::Token::FractionDigitsTag)]);
				if (fractionDigitNode.hasAttr(XSDFrontend::Token::ValueAttr))
				{
					setFractionDigits(std::stoi(fractionDigitNode.getAttr(XSDFrontend::Token::ValueAttr)));
				}
			}

			if (node.hasChild(XSDFrontend::Token::TotalDigitsTag))
			{
				const auto &totalDigitNode(node.getChildren()[node.findChild(XSDFrontend::Token::TotalDigitsTag)]);
				if (totalDigitNode.hasAttr(XSDFrontend::Token::ValueAttr))
				{
					setTotalDigits(std::stoi(totalDigitNode.getAttr(XSDFrontend::Token::ValueAttr)));
				}
			}

			return true;
		}

		NumberVariant XSDString2NumberVairant(const std::string & str)
		{
			//! to do
			return NumberVariant();
		}
	};
};
