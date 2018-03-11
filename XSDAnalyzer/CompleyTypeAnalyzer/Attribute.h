#pragma once

#include "AttributeInterface.h"

#include <map>
#include <memory>

namespace XSDFrontend
{
	namespace Attribute
	{
		class Attribute final : public IAttributeInterface, 
			public XSDElementUtils::IXSDNamedTypedElementInterface, 
			public XSDElementUtils::IXSDValueStatedElementInterface, 
			public XSDElementUtils::IXSDReferenceElementInterface<Attribute>
		{
		public:
			enum class eForm
			{
				Qualified,
				Unqualified
			};

			enum class eUse
			{
				Optional,
				Prohibited,
				Required
			};

		public:
			Attribute(const eForm form = eForm::Unqualified, const eUse use = eUse::Optional);
			Attribute(const std::string &name, const std::string &type, const eForm form = eForm::Unqualified, const eUse use = eUse::Optional);
			Attribute(std::string &&name, const std::string &type, const eForm form = eForm::Unqualified, const eUse use = eUse::Optional);
			Attribute(std::string &&name, std::string &&type, const eForm form = eForm::Unqualified, const eUse use = eUse::Optional);
			Attribute(const Attribute &ano) = default;
			Attribute(Attribute &&ano) = default;
			Attribute &operator=(const Attribute &rhs) = default;
			Attribute &operator=(Attribute &&rhs) = default;
			~Attribute(void) = default;

			inline void setForm(const eForm form) { m_form = form; }
			inline const eForm getForm(void) const { return m_form; }

			inline void setUse(const eUse use) { m_use = use; }
			inline const eUse getUse(void) const { return m_use; }

		private:
			eForm m_form;
			eUse m_use;
		};

		extern const std::map<std::string, Attribute::eForm> FormString2Form;
		extern const std::map<std::string, Attribute::eUse> UseString2Use;
	};
};
