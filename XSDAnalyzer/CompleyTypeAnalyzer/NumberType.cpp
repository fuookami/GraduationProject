#include "NumberType.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const SSUtils::Math::Real ValueLimitConfiguration<SSUtils::Math::Real>::NoValueValidator = SSUtils::Math::Real();
		const std::map<std::string, NumberType::eBaseType> NumberType::String2Type =
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

		NumberType::NumberType(void)
			: NumberType("")
		{
		}

		NumberType::NumberType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
			ValueLimitConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
		}

		NumberType::NumberType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tNumberType), ValueLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_fractionDigits(NoDigitValidator), m_totalDigits(NoDigitValidator)
		{
			ValueLimitConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
		}

		const bool NumberType::refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node)
		{
			if (!refreshValueLimitConfiguration(node, std::bind(XSDString2NumberVairant, m_baseType, std::placeholders::_1)))
			{
				return false;
			}
			refreshValueEnumrationConfiguration(node, std::bind(XSDString2NumberVairant, m_baseType, std::placeholders::_1));

			if (node->hasChild(XSDFrontend::Token::FractionDigitsTag))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::FractionDigitsTag)]);
				if (child != nullptr && child->hasAttr(XSDFrontend::Token::ValueAttr))
				{
					setFractionDigits(std::stoi(child->getAttr(XSDFrontend::Token::ValueAttr)));
				}
			}

			if (node->hasChild(XSDFrontend::Token::TotalDigitsTag))
			{
				auto child(node->getChildren()[node->findChild(XSDFrontend::Token::TotalDigitsTag)]);
				if (child != nullptr && child->hasAttr(XSDFrontend::Token::ValueAttr))
				{
					setTotalDigits(std::stoi(child->getAttr(XSDFrontend::Token::ValueAttr)));
				}
			}

			return true;
		}

		void NumberType::setBaseType(const eBaseType baseType)
		{
			m_baseType = baseType;
			ValueLimitConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
			ValueEnumrationConfiguration<SSUtils::Math::Real>::DefaultTranslator = std::bind(XSDString2NumberVairant, baseType, std::placeholders::_1);
		}

		SSUtils::Math::Real XSDString2NumberVairant(const NumberType::eBaseType type, const std::string & _str)
		{
			static const std::string ScientificNotationPattern("^(-?(0|[1-9]\\d*)(.\\d*))?e(-?(0|[1-9]\\d*))$");
			static const std::string PositiveZero("+0"), NegetiveZero("-0");

			std::string str;
			std::transform(_str.cbegin(), _str.cbegin(), std::back_inserter(str), tolower);
			if (SSUtils::String::RegexChecker(ScientificNotationPattern)(str))
			{
				std::vector<std::string> parts(SSUtils::String::split(str, std::string("e")));
				return SSUtils::Math::Real(SSUtils::Math::Decimal(parts[0], std::stoi(parts[1])));
			}
			else if (str == PositiveZero || str == NegetiveZero)
			{
				return SSUtils::Math::Real(SSUtils::Math::Integer(0));
			}
			else
			{
				return SSUtils::Math::Real(str);
			}
		}
	};
};
