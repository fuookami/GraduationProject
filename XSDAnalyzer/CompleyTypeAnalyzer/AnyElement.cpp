#include "AnyElement.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const std::string AnyElement::MaxOccursUnboundedString("unbounded");

		const boost::bimap<std::string, AnyElement::eNamespaceValidator> AnyElement::String2NamespaceValidator =
			[]()
		{
			typedef boost::bimap<std::string, AnyElement::eNamespaceValidator> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("##any"), AnyElement::eNamespaceValidator::Any));
			ret.insert(pair_type(std::string("##other"), AnyElement::eNamespaceValidator::Other));
			ret.insert(pair_type(std::string("##local"), AnyElement::eNamespaceValidator::Local));
			ret.insert(pair_type(std::string("##targetNamespace"), AnyElement::eNamespaceValidator::TargetNamespace));
			return ret;
		}();

		const boost::bimap<std::string, AnyElement::eProcessContents> AnyElement::String2ProcessContents =
			[]()
		{
			typedef boost::bimap<std::string, AnyElement::eProcessContents> result_type;
			typedef result_type::value_type pair_type;

			result_type ret;
			ret.insert(pair_type(std::string("strict"), AnyElement::eProcessContents::Strict));
			ret.insert(pair_type(std::string("lax"), AnyElement::eProcessContents::Lax));
			ret.insert(pair_type(std::string("skip"), AnyElement::eProcessContents::Skip));
			return ret;
		}();

		AnyElement::AnyElement(const int minOccurs, const int maxOccurs, const eNamespaceValidator namesapceValidator, const eProcessContents processContents)
			: IElementInterface(IElementInterface::eElementType::tAnyElement), 
			m_namespaceValidator(namesapceValidator), m_processContents(processContents)
		{
			setMinOccurs(minOccurs);
			setMaxOccurs(maxOccurs);
		}
	};
};
