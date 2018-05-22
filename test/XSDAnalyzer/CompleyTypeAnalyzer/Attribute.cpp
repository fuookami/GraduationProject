#include "Attribute.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		const boost::bimap<std::string, Attribute::eForm> Attribute::String2Form =
			[]()
		{
			typedef boost::bimap<std::string, Attribute::eForm> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("qualified"), Attribute::eForm::Qualified));
			ret.insert(pair_type(std::string("unqualified"), Attribute::eForm::Unqualified));
			return ret;
		}();

		const boost::bimap<std::string, Attribute::eUse> Attribute::String2Use =
			[]()
		{
			typedef boost::bimap<std::string, Attribute::eUse> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("optional"), Attribute::eUse::Optional));
			ret.insert(pair_type(std::string("required"), Attribute::eUse::Required));
			ret.insert(pair_type(std::string("prohibited"), Attribute::eUse::Prohibited));
			return ret;
		}();

		const std::set<std::string> Attribute::BaseAttrs = 
		{
			Token::DefaultAttr, Token::FixedAttr, Token::FormAttr, Token::NameAttr, Token::ReferenceAttr, Token::TypeAttr, Token::UseAttr
		};

		Attribute::Attribute(const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(const std::string & name, const std::string & type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(name, type), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(std::string && name, const std::string & type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), type), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(), 
			m_form(form), m_use(use)
		{
		}

		Attribute::Attribute(std::string && name, std::string && type, const eForm form, const eUse use)
			: IAttributeInterface(IAttributeInterface::eAttributeType::tAttribute), IXSDNamedTypedElementInterface(std::move(name), std::move(type)), IXSDValueStatedElementInterface(), IXSDReferenceElementInterface(),
			m_form(form), m_use(use)
		{
		}
	};
};
