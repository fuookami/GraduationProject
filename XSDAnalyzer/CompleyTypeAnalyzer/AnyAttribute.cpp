#include "AnyAttribute.h"

namespace XSDFrontend
{
	namespace Attribute
	{
		const std::map<std::string, AnyAttribute::eNamespaceValidator> NamespaceValidatorString2Validator =
		{
			std::make_pair(std::string("##any"), AnyAttribute::eNamespaceValidator::Any),
			std::make_pair(std::string("##other"), AnyAttribute::eNamespaceValidator::Other),
			std::make_pair(std::string("##local"), AnyAttribute::eNamespaceValidator::Local),
			std::make_pair(std::string("##targetNamespace"), AnyAttribute::eNamespaceValidator::TargetNamespace)
		};

		const std::map<std::string, AnyAttribute::eProcessContents> ProcessContentsString2ProcessContents =
		{
			std::make_pair(std::string("strict"), AnyAttribute::eProcessContents::Strict),
			std::make_pair(std::string("lax"), AnyAttribute::eProcessContents::Lax),
			std::make_pair(std::string("skip"), AnyAttribute::eProcessContents::Skip)
		};
	};
};
