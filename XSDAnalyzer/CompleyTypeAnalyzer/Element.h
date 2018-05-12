#pragma once

#include "ElementInterface.h"
#include "XSDElementUtils.h"

#include <memory>
#include <set>

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
				tComplexContent,
				tUnknown
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

			static const std::map<std::string, eForm> String2Form;
			static const std::map<std::string, bool> String2Nillable;
			static const std::map<std::string, bool> String2Abastract;
			static const std::map<std::string, eBlock> String2Block;
			static const std::map<std::string, eFinal> String2Final;

		public:
			Element(const eCategory category = eCategory::tUnknown, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &name, const eCategory category = eCategory::tUnknown, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(std::string &&name, const eCategory category = eCategory::tUnknown, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const std::string &name, const std::string &type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(std::string &&name, const std::string &type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(std::string &&name, std::string &&type, const eCategory category, const eForm form = eForm::Unqualified, const eBlock block = eBlock::NonBlock, const eFinal _final = eFinal::NonFinal);
			Element(const Element &ano) = default;
			Element(Element &&ano) = default;
			Element &operator=(const Element &rhs) = default;
			Element &operator=(Element &&rhs) = default;
			~Element(void) = default;

			inline void setCategory(const eCategory &category) { m_category = category; }
			inline const eCategory getCategory(void) const { return m_category; }

			inline void setSubstitutionGroup(const std::string &name) { m_substitutionGroup.assign(name); }
			inline void setSubstitutionGroup(std::string &&name) { m_substitutionGroup.assign(std::move(name)); }
			inline const std::string &getSubstitutionGroup(void) const { return m_substitutionGroup; }

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

			std::set<std::string> suppliedTokens(void) const;
			std::set<std::string> neededTokens(void) const;

		private:
			inline const bool valueStatedEnabled(void) const { return m_category == eCategory::tBaseType || m_category == eCategory::tSimpleType; }

		private:
			eCategory m_category;
			std::string m_substitutionGroup;

			eForm m_form;
			bool m_nillable;
			bool m_abstract;
			eBlock m_block;
			eFinal m_final;
		};
	};
};
