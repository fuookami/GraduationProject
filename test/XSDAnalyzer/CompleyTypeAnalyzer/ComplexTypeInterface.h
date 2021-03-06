#pragma once

#include "XSDElementUtils.h"

#include <set>
#include <boost/bimap.hpp>

namespace XSDFrontend
{
	namespace ComplexType
	{
		enum class eComplexType
		{
			tSimpleContent,
			tComplexContent
		};

		class IComplexTypeInterface abstract : public XSDElementUtils::IXSDNamedElementInterface,
			public XSDElementUtils::IXSDExtraAttributeInterface
		{
		public:
			enum class eDerivedType
			{
				tNone,
				tRestriction,
				tExtension,
			};

			enum class eBlock
			{
				tNone,
				tExtension,
				tRestriction,
				tAll
			};

			enum class eFinal
			{
				tNone,
				tExtension,
				tRestriction,
				tAll
			};

			static const boost::bimap<std::string, bool> String2Abstract;
			static const boost::bimap<std::string, bool> String2Mixed;
			static const boost::bimap<std::string, eComplexType> Tag2ComplexType;
			static const boost::bimap<std::string, eDerivedType> Tag2DerivedType;
			static const boost::bimap<std::string, IComplexTypeInterface::eBlock> String2Block;
			static const boost::bimap<std::string, IComplexTypeInterface::eFinal> String2Final;
			static const std::set<std::string> BaseAttrs;
			static const bool DefaultAbstract = false;
			static const bool DefaultMixed = false;
			static const eBlock DefaultBlock = eBlock::tNone;
			static const eFinal DefaultFinal = eFinal::tNone;

		protected:
			IComplexTypeInterface(const eComplexType type);
			IComplexTypeInterface(const std::string &name, const eComplexType type);
			IComplexTypeInterface(std::string &&name, const eComplexType type);
			IComplexTypeInterface(const IComplexTypeInterface &ano) = default;
			IComplexTypeInterface(IComplexTypeInterface &&ano) = default;
			IComplexTypeInterface &operator=(const IComplexTypeInterface &rhs) = default;
			IComplexTypeInterface &operator=(IComplexTypeInterface &&rhs) = default;
		public:
			virtual ~IComplexTypeInterface(void) = default;

		public:
			inline void setComplexType(const eComplexType type) { m_type = type; }
			inline const eComplexType getComplexType(void) const { return m_type; }

			inline void setAbstract(const bool _abstract) { m_abstract = _abstract; }
			inline const bool getAbstract(void) const { return m_abstract; }

			inline void setMixed(const bool mixed) { m_mixed = mixed; }
			inline const bool getMixed(void) const { return m_mixed; }

			inline void setBlock(const eBlock block) { m_block = block; }
			inline const eBlock getBlock(void) const { return m_block; }

			inline void setFinal(const eFinal _final) { m_final = _final; }
			inline const eFinal getFinal(void) const { return m_final; }

			inline void setBaseType(const eDerivedType deriveType, const std::string &baseTypeName) { m_deriveType = deriveType; m_baseTypeName.assign(baseTypeName); }
			inline void setBaseType(const eDerivedType deriveType, const std::string &&baseTypeName) { m_deriveType = deriveType; m_baseTypeName.assign(std::move(baseTypeName)); }
			inline const eDerivedType getDeriveType(void) const { return m_deriveType; }
			inline const std::string &getBaseTypeName(void) const { return m_baseTypeName; }

			inline void setAttributeGroupName(const std::string &attributeGroupName) { m_attributeGroup.assign(attributeGroupName); }
			inline void setAttributeGroupName(const std::string &&attributeGroupName) { m_attributeGroup.assign(std::move(attributeGroupName)); }
			inline const std::string &getAttributeGroupName(void) const { return m_attributeGroup; }

			virtual std::set<std::string> suppliedTokens(void) const;
			virtual std::set<std::string> neededTokens(void) const;

		private:
			eComplexType m_type;

			bool m_abstract;
			bool m_mixed;

			eBlock m_block;
			eFinal m_final;

			eDerivedType m_deriveType;
			std::string m_baseTypeName;
			std::string m_attributeGroup;
		};
	};
};
