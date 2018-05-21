#include "SimpleTypeInterface.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		const boost::bimap<std::string, ISimpleTypeInterface::eWhiteSpace> ISimpleTypeInterface::String2WhiteSpace =
			[]()
		{
			typedef boost::bimap<std::string, ISimpleTypeInterface::eWhiteSpace> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("preserve"), ISimpleTypeInterface::eWhiteSpace::Preserve));
			ret.insert(pair_type(std::string("replace"), ISimpleTypeInterface::eWhiteSpace::Replace));
			ret.insert(pair_type(std::string("collapse"), ISimpleTypeInterface::eWhiteSpace::Collapse));
			return ret;
		}();

		const std::set<std::string> ISimpleTypeInterface::BaseAttrs = 
		{
			Token::NameAttr
		};

		ISimpleTypeInterface::ISimpleTypeInterface(const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(const std::string & name, const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(name), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		ISimpleTypeInterface::ISimpleTypeInterface(std::string && name, const eSimpleType type, const eWhiteSpace whitSpace)
			: IXSDNamedElementInterface(std::move(name)), 
			m_type(type), m_whiteSpace(whitSpace), m_baseTypeName()
		{
		}

		std::set<std::string> ISimpleTypeInterface::suppliedTokens(void) const
		{
			std::set<std::string> ret;
			if (!getAnonymous() && !getName().empty())
			{
				ret.insert(getName());
			}
			return ret;
		}

		std::set<std::string> ISimpleTypeInterface::neededTokens(void) const
		{
			std::set<std::string> ret;
			if (!m_baseTypeName.empty())
			{
				ret.insert(m_baseTypeName);
			}
			return ret;
		}

		std::shared_ptr<SSUtils::XML::Node> ISimpleTypeInterface::saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const
		{
			if (!getBaseTypeName().empty())
			{
				root->setAttr(XSDFrontend::Token::BaseTypeAttr, getBaseTypeName());
			}
			if (m_whiteSpace != DefaultWhiteSpace)
			{
				auto node(SSUtils::XML::Node::generate(XSDFrontend::Token::WhiteSpaceTag));
				node->setAttr(XSDFrontend::Token::ValueAttr, String2WhiteSpace.right.find(m_whiteSpace)->second);
				root->addChild(node);
			}
			return root;
		}
	};
};
