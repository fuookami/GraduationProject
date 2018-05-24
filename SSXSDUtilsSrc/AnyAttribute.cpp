#include "stdafx.h"
#include "AnyAttribute.h"
#include "XSDToken.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		const boost::bimap<std::string, AnyAttribute::eNamespaceValidator> AnyAttribute::String2NamespaceValidator =
			[]()
		{
			typedef boost::bimap<std::string, AnyAttribute::eNamespaceValidator> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("##any"), AnyAttribute::eNamespaceValidator::Any));
			ret.insert(pair_type(std::string("##other"), AnyAttribute::eNamespaceValidator::Other));
			ret.insert(pair_type(std::string("##local"), AnyAttribute::eNamespaceValidator::Local));
			ret.insert(pair_type(std::string("##targetNamespace"), AnyAttribute::eNamespaceValidator::TargetNamespace));
			return ret;
		}();

		const boost::bimap<std::string, AnyAttribute::eProcessContents> AnyAttribute::String2ProcessContents =
			[]()
		{
			typedef boost::bimap<std::string, AnyAttribute::eProcessContents> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("strict"), AnyAttribute::eProcessContents::Strict));
			ret.insert(pair_type(std::string("lax"), AnyAttribute::eProcessContents::Lax));
			ret.insert(pair_type(std::string("skip"), AnyAttribute::eProcessContents::Skip));
			return ret;
		}();

		const std::set<std::string> AnyAttribute::BaseAttrs = 
		{
			Token::NamesapceAttr(), Token::ProcessContentsAttr()
		};
	};
};
