#pragma once

#include "ElementInterface.h"

#include <map>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class AnyElement final : public IElementInterface
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
			static const int MaxOccursUnbounded = -1;
			static const std::map<std::string, AnyElement::eNamespaceValidator> String2NamespaceValidator;
			static const std::map<std::string, AnyElement::eProcessContents> String2ProcessContents;

		public:
			AnyElement(const int minOccurs = 1, const int maxOccurs = 1, const eNamespaceValidator namesapceValidator = eNamespaceValidator::Any, const eProcessContents processContents = eProcessContents::Skip);
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
