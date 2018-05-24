#pragma once

#include "AttributeInterface.h"

#include <map>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace Attribute
	{
		class SSXSDUtils_API_DECLSPEC AnyAttribute final : public IAttributeInterface,
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

			static const boost::bimap<std::string, AnyAttribute::eNamespaceValidator> String2NamespaceValidator;
			static const boost::bimap<std::string, AnyAttribute::eProcessContents> String2ProcessContents;
			static const std::set<std::string> BaseAttrs;
			static const eNamespaceValidator DefaultNamespaceValidator = eNamespaceValidator::Any;
			static const eProcessContents DefaultProcessContents = eProcessContents::Skip;

		public:
			AnyAttribute(const eNamespaceValidator namesapceValidator = DefaultNamespaceValidator, const eProcessContents processContents = DefaultProcessContents) : IAttributeInterface(IAttributeInterface::eAttributeType::tAnyAttribute), m_namespaceValidator(namesapceValidator), m_processContents(processContents) {};
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
	};
};
