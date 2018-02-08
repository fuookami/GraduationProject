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

		static const std::map<std::string, AnyElement::eNamespaceValidator> NamespaceValidatorString2Validator =
		{
			std::make_pair(std::string("##any"), AnyElement::eNamespaceValidator::Any),
			std::make_pair(std::string("##other"), AnyElement::eNamespaceValidator::Other),
			std::make_pair(std::string("##local"), AnyElement::eNamespaceValidator::Local),
			std::make_pair(std::string("##targetNamespace"), AnyElement::eNamespaceValidator::TargetNamespace)
		};

		static const std::map<std::string, AnyElement::eProcessContents> ProcessContentsString2ProcessContents =
		{
			std::make_pair(std::string("strict"), AnyElement::eProcessContents::Strict),
			std::make_pair(std::string("lax"), AnyElement::eProcessContents::Lax),
			std::make_pair(std::string("skip"), AnyElement::eProcessContents::Skip)
		};
	};
};
