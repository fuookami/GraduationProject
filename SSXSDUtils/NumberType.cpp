#include "NumberType.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const SSUtils::Math::Real ValueLimitConfiguration<SSUtils::Math::Real>::NoValueValidator = SSUtils::Math::Real();
		const boost::bimap<std::string, NumberType::eBaseType> NumberType::String2Type =
			[]()
		{
			typedef boost::bimap<std::string, NumberType::eBaseType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("boolean"), NumberType::eBaseType::tBoolean));
			ret.insert(pair_type(std::string("float"), NumberType::eBaseType::tFloat));
			ret.insert(pair_type(std::string("double"), NumberType::eBaseType::tDouble));
			ret.insert(pair_type(std::string("decimal"), NumberType::eBaseType::tDecimal));
			ret.insert(pair_type(std::string("integer"), NumberType::eBaseType::tInteger));
			ret.insert(pair_type(std::string("nonPositiveInteger"), NumberType::eBaseType::tNonPositiveInteger));
			ret.insert(pair_type(std::string("negativeInteger"), NumberType::eBaseType::tNegativeInteger));
			ret.insert(pair_type(std::string("long"), NumberType::eBaseType::tLong));
			ret.insert(pair_type(std::string("int"), NumberType::eBaseType::tInt));
			ret.insert(pair_type(std::string("short"), NumberType::eBaseType::tShort));
			ret.insert(pair_type(std::string("byte"), NumberType::eBaseType::tByte));
			ret.insert(pair_type(std::string("nonNegativeInteger"), NumberType::eBaseType::tNonNegativeInteger));
			ret.insert(pair_type(std::string("positiveInteger"), NumberType::eBaseType::tPositiveInteger));
			ret.insert(pair_type(std::string("unsignedLong"), NumberType::eBaseType::tUnsignedLong));
			ret.insert(pair_type(std::string("unsignedInt"), NumberType::eBaseType::tUnsignedInt));
			ret.insert(pair_type(std::string("unsignedShort"), NumberType::eBaseType::tUnsignedShort));
			ret.insert(pair_type(std::string("unsignedBytes"), NumberType::eBaseType::tUnsignedByte));

			return ret;
		}();

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

		std::shared_ptr<SSUtils::XML::Node> NumberType::saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const
		{
			root->setAttr(XSDFrontend::Token::BaseTypeAttr, XSDFrontend::Token::XSNamespace + String2Type.right.find(m_baseType)->second);
			ISimpleTypeInterface::saveValidator(root);
			if (m_fractionDigits >= 0)
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::FractionDigitsTag));
				node->setAttr(XSDFrontend::Token::ValueAttr, std::to_string(m_fractionDigits));
				root->addChild(node);
			}
			if (m_totalDigits >= 0)
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::TotalDigitsTag));
				node->setAttr(XSDFrontend::Token::ValueAttr, std::to_string(m_totalDigits));
				root->addChild(node);
			}
			saveValueEnumrationConfiguration(root);
			saveValueLimitConfiguration(root);

			return root;
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
