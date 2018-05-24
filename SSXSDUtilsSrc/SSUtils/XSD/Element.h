#pragma once

#include "ElementInterface.h"
#include "XSDElementUtils.h"

#include <memory>
#include <set>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class SSXSDUtils_API_DECLSPEC Element final : public IElementInterface,
			public XSDElementUtils::IXSDNamedTypedElementInterface, 
			public XSDElementUtils::IXSDExtraAttributeInterface, 
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

			static const boost::bimap<std::string, eForm> String2Form;
			static const boost::bimap<std::string, bool> String2Nillable;
			static const boost::bimap<std::string, bool> String2Abstract;
			static const boost::bimap<std::string, eBlock> String2Block;
			static const boost::bimap<std::string, eFinal> String2Final;
			static const std::set<std::string> BaseAttrs;
			static const eCategory DefaultCategory = eCategory::tUnknown;
			static const eForm DefaultForm = eForm::Unqualified;
			static const eBlock DefaultBlock = eBlock::NonBlock;
			static const eFinal DefaultFinal = eFinal::NonFinal;
			static const bool DefaultNillable = false;
			static const bool DefaultAbstract = false;

		public:
			Element(const eCategory category = DefaultCategory, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
			Element(const std::string &name, const eCategory category = DefaultCategory, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
			Element(std::string &&name, const eCategory category = DefaultCategory, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
			Element(const std::string &name, const std::string &type, const eCategory category, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
			Element(std::string &&name, const std::string &type, const eCategory category, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
			Element(std::string &&name, std::string &&type, const eCategory category, const eForm form = DefaultForm, const eBlock block = DefaultBlock, const eFinal _final = DefaultFinal);
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
