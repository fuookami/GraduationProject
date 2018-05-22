#pragma once

#include "ElementInterface.h"

#include <map>
#include <set>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class AnyElement final : public IElementInterface, 
			public XSDElementUtils::IXSDExtraAttributeInterface
		{
		public:
			enum class eNamespaceValidator
			{
				Any,
				Other,
				Local,
				TargetNamespace
			};

			enum class eProcessContents
			{
				Strict,
				Lax,
				Skip
			};

			static const std::string MaxOccursUnboundedString;
			static const boost::bimap<std::string, AnyElement::eNamespaceValidator> String2NamespaceValidator;
			static const boost::bimap<std::string, AnyElement::eProcessContents> String2ProcessContents;
			static const std::set<std::string> BaseAttrs;
			static const eNamespaceValidator DefaultNamespaceValidator = eNamespaceValidator::Any;
			static const eProcessContents DefaultProcessContents = eProcessContents::Skip;

		public:
			AnyElement(const int minOccurs = 1, const int maxOccurs = 1, const eNamespaceValidator namesapceValidator = DefaultNamespaceValidator, const eProcessContents processContents = DefaultProcessContents);
			AnyElement(const AnyElement &ano) = default;
			AnyElement(AnyElement &&ano) = default;
			AnyElement &operator=(const AnyElement &rhs) = default;
			AnyElement &operator=(AnyElement &&rhs) = default;
			~AnyElement(void) = default;

			inline void setNamespaceValidator(const eNamespaceValidator namespaceValidator) { m_namespaceValidator = namespaceValidator; }
			inline const eNamespaceValidator getNamesapceValidator(void) const { return m_namespaceValidator; }

			inline void setProcessContents(const eProcessContents processContents) { m_processContents = processContents; }
			inline const eProcessContents getProcessContents(void) const { return m_processContents; }

		private:
			eNamespaceValidator m_namespaceValidator;
			eProcessContents m_processContents;
		};
	};
};
