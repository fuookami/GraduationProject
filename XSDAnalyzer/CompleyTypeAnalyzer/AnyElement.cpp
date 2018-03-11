#include "AnyElement.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		const std::string AnyElement::MaxOccursUnboundedString("unbounded");

		AnyElement::AnyElement(const int minOccurs, const int maxOccurs, const eNamespaceValidator namesapceValidator, const eProcessContents processContents)
			: IElementInterface(IElementInterface::eElementType::tAnyElement), 
			m_namespaceValidator(namesapceValidator), m_processContents(processContents)
		{
			setMinOccurs(minOccurs);
			setMaxOccurs(maxOccurs);
		}

		const std::map<std::string, AnyElement::eNamespaceValidator> NamespaceValidatorString2Validator =
		{
			std::make_pair(std::string("##any"), AnyElement::eNamespaceValidator::Any),
			std::make_pair(std::string("##other"), AnyElement::eNamespaceValidator::Other),
			std::make_pair(std::string("##local"), AnyElement::eNamespaceValidator::Local),
			std::make_pair(std::string("##targetNamespace"), AnyElement::eNamespaceValidator::TargetNamespace)
		};

		const std::map<std::string, AnyElement::eProcessContents> ProcessContentsString2ProcessContents =
		{
			std::make_pair(std::string("strict"), AnyElement::eProcessContents::Strict),
			std::make_pair(std::string("lax"), AnyElement::eProcessContents::Lax),
			std::make_pair(std::string("skip"), AnyElement::eProcessContents::Skip)
		};
	};
};
