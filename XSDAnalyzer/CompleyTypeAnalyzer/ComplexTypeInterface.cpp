#include "ComplexTypeInterface.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const boost::bimap<std::string, bool> IComplexTypeInterface::String2Abstract =
			[]()
		{
			typedef boost::bimap<std::string, bool> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(SSUtils::String::True, true));
			ret.insert(pair_type(SSUtils::String::False, true));
			return ret;
		}();

		const boost::bimap<std::string, bool> IComplexTypeInterface::String2Mixed =
			[]()
		{
			typedef boost::bimap<std::string, bool> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(SSUtils::String::True, true));
			ret.insert(pair_type(SSUtils::String::False, false));
			return ret;
		}();

		const boost::bimap<std::string, eComplexType> IComplexTypeInterface::Tag2ComplexType = 
			[]()
		{
			typedef boost::bimap<std::string, eComplexType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(Token::SimpleContentTag, eComplexType::tSimpleContent));
			ret.insert(pair_type(Token::ComplexContentTag, eComplexType::tComplexContent));
			return ret;
		}();

		const boost::bimap<std::string, IComplexTypeInterface::eDerivedType> IComplexTypeInterface::Tag2DerivedType = 
			[]()
		{
			typedef boost::bimap<std::string, IComplexTypeInterface::eDerivedType> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(Token::RestrictionTag, IComplexTypeInterface::eDerivedType::tRestriction));
			ret.insert(pair_type(Token::ExtensionTag, IComplexTypeInterface::eDerivedType::tExtension));
			return ret;
		}();

		const boost::bimap<std::string, IComplexTypeInterface::eBlock> IComplexTypeInterface::String2Block =
			[]()
		{
			typedef boost::bimap<std::string, IComplexTypeInterface::eBlock> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("extension"), IComplexTypeInterface::eBlock::tExtension));
			ret.insert(pair_type(std::string("restriction"), IComplexTypeInterface::eBlock::tRestriction));
			ret.insert(pair_type(std::string("#all"), IComplexTypeInterface::eBlock::tAll));
			return ret;
		}();

		const boost::bimap<std::string, IComplexTypeInterface::eFinal> IComplexTypeInterface::String2Final =
			[]()
		{
			typedef boost::bimap<std::string, IComplexTypeInterface::eFinal> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("extension"), IComplexTypeInterface::eFinal::tExtension));
			ret.insert(pair_type(std::string("restriction"), IComplexTypeInterface::eFinal::tRestriction));
			ret.insert(pair_type(std::string("#all"), IComplexTypeInterface::eFinal::tAll));
			return ret;
		}();

		const std::set<std::string> IComplexTypeInterface::BaseAttrs = 
		{
			Token::NameAttr, Token::AbstractAttr, Token::MixedAttr, Token::BlockAttr, Token::FinalAttr
		};

		IComplexTypeInterface::IComplexTypeInterface(const eComplexType type)
			: IXSDNamedElementInterface(), 
			m_type(type), m_abstract(false), m_mixed(false), 
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(const std::string & name, const eComplexType type)
			: IXSDNamedElementInterface(name), 
			m_type(type), m_abstract(false), m_mixed(false),
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		IComplexTypeInterface::IComplexTypeInterface(std::string && name, const eComplexType type)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_abstract(false), m_mixed(false),
			m_block(eBlock::tNone), m_final(eFinal::tNone), 
			m_deriveType(eDerivedType::tNone), m_baseTypeName(), m_attributeGroup()
		{
		}

		std::set<std::string> IComplexTypeInterface::suppliedTokens(void) const
		{
			std::set<std::string> ret;
			ret.insert(getName());
			return ret;
		}

		std::set<std::string> IComplexTypeInterface::neededTokens(void) const
		{
			std::set<std::string> ret;
			if (m_deriveType != eDerivedType::tNone)
			{
				ret.insert(m_baseTypeName);
			}
			if (!m_attributeGroup.empty())
			{
				ret.insert(m_attributeGroup);
			}
			return ret;
		}
	};
};
