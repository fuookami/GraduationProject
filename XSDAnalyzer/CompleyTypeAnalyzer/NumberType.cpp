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

		const std::map<std::string, NumberType::eBaseType> NumberBaseTypeName2Type =
		{
			std::make_pair(std::string("boolean"), NumberType::eBaseType::tBoolean),
			std::make_pair(std::string("float"), NumberType::eBaseType::tFloat),
			std::make_pair(std::string("double"), NumberType::eBaseType::tDouble),
			std::make_pair(std::string("decimal"), NumberType::eBaseType::tDecimal),
			std::make_pair(std::string("integer"), NumberType::eBaseType::tInteger),
			std::make_pair(std::string("nonPositiveInteger"), NumberType::eBaseType::tNonPositiveInteger),
			std::make_pair(std::string("negativeInteger"), NumberType::eBaseType::tNegativeInteger),
			std::make_pair(std::string("long"), NumberType::eBaseType::tLong),
			std::make_pair(std::string("int"), NumberType::eBaseType::tInt),
			std::make_pair(std::string("short"), NumberType::eBaseType::tShort),
			std::make_pair(std::string("byte"), NumberType::eBaseType::tByte),
			std::make_pair(std::string("nonNegativeInteger"), NumberType::eBaseType::tNonNegativeInteger),
			std::make_pair(std::string("positiveInteger"), NumberType::eBaseType::tPositiveInteger),
			std::make_pair(std::string("unsignedLong"), NumberType::eBaseType::tUnsignedLong),
			std::make_pair(std::string("unsignedInt"), NumberType::eBaseType::tUnsignedInt),
			std::make_pair(std::string("unsignedShort"), NumberType::eBaseType::tUnsignedShort),
			std::make_pair(std::string("unsignedBytes"), NumberType::eBaseType::tUnsignedByte)
		};

		NumberVariant XSDString2NumberVairant(const std::string & str)
		{
			//! to do
			return NumberVariant();
		}
	};
};
