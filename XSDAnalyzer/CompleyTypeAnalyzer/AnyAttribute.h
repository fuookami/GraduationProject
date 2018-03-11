#pragma once

#include "AttributeInterface.h"

#include <map>

namespace XSDFrontend
{
	namespace Attribute
	{
		class AnyAttribute final : public IAttributeInterface
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

		public:
			AnyAttribute(const eNamespaceValidator namesapceValidator = eNamespaceValidator::Any, const eProcessContents processContents = eProcessContents::Skip) : IAttributeInterface(IAttributeInterface::eAttributeType::tAnyAttribute), m_namespaceValidator(namesapceValidator), m_processContents(processContents) {};
			AnyAttribute(const AnyAttribute &ano) = default;
			AnyAttribute(AnyAttribute &&ano) = default;
			AnyAttribute &operator=(const AnyAttribute &rhs) = default;
			AnyAttribute &operator=(AnyAttribute &&rhs) = default;
			~AnyAttribute(void) = default;

			inline void setNamespaceValidator(const eNamespaceValidator namespaceValidator) { m_namespaceValidator = namespaceValidator; }
			inline const eNamespaceValidator getNamesapceValidator(void) const { return m_namespaceValidator; }

			inline void setProcessContents(const eProcessContents processContents) { m_processContents = processContents; }
			inline const eProcessContents getProcessContents(void) const { return m_processContents; }

		private:
			eNamespaceValidator m_namespaceValidator;
			eProcessContents m_processContents;
		};

		extern const std::map<std::string, AnyAttribute::eNamespaceValidator> NamespaceValidatorString2Validator;
		extern const std::map<std::string, AnyAttribute::eProcessContents> ProcessContentsString2ProcessContents;
	};
};
