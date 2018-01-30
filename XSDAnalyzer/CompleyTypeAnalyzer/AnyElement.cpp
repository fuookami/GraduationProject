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
	};
};
