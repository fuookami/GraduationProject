#pragma once

#include "ElementInterface.h"
#include "XSDElementUtils.h"

#include <memory>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class Element final : public IElementInterface,
			public XSDElementUtils::IXSDNamedTypedElementInterface,
			public XSDElementUtils::IXSDReferenceElementInterface<Element>,
			public XSDElementUtils::IXSDValueStatedElementInterface
		{
		public:
			enum class eCategory
			{
				tBaseType,
				tSimpleType,
				tSimpleContent,
				tComplexContent
			};

			enum class eForm
			{
				Qualified,
				Unqualified
			};

			enum class eBlock
			{
				NonBlock,
				Extension,
				Restriction,
				Substitution,
				All
			};

			enum class eFinal
			{
				NonFinal,
				Extension,
				Restriction,
				All
			};

		public:
			Element(const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &name, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &&name, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &name, const std::string &type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &&name, const std::string &type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &&name, const std::string &&type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const Element &ano);
			Element(const Element &&ano);
			Element &operator=(const Element &rhs);
			Element &operator=(const Element &&rhs);
			~Element(void);

			inline void setCategory(const eCategory &category) { m_category = category; }
			inline const eCategory getCategory(void) const { return m_category; }

			inline void setForm(const eForm form) { m_form = form; }
			inline const eForm getForm(void) const { return m_form; }

			inline void setNillable(const bool nillable) { m_nillable = nillable; }
			inline const bool getNillable(void) const { return m_nillable; }

			inline void setAbstract(const bool _abstract) { m_abstract = _abstract; }
			inline const bool getAbstract(void) const { return m_abstract; }

			inline void setBlock(const eBlock block) { m_block = block; }
			inline const eBlock getBlock(void) const { return m_block; }

			inline void setFinal(const eFinal _final) { m_final = _final; }
			inline const eFinal getFinal(void) const { return m_final; }

		private:
			inline const bool valueStatedEnabled(void) const { return m_category == eCategory::tBaseType || m_category == eCategory::tSimpleType; }

		private:
			eCategory m_category;

			eForm m_form;
			bool m_nillable;
			bool m_abstract;
			eBlock m_block;
			eFinal m_final;
		};
	};
};
