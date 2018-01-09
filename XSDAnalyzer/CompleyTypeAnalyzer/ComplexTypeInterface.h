#pragma once

#include "XSDElementUtils.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		enum class eComplexType
		{
			tSimpleContent,
			tComplexContent
		};

		class IComplexTypeInterface abstract : public XSDElementUtils::IXSDNamedElementInterface
		{
		public:
			enum class eDerivedType
			{
				tNone,
				tRestriction,
				tExtension,
			};

		protected:
			IComplexTypeInterface(const eComplexType type);
			IComplexTypeInterface(const std::string &name, const eComplexType type);
			IComplexTypeInterface(const std::string &&name, const eComplexType type);
			IComplexTypeInterface(const IComplexTypeInterface &ano);
			IComplexTypeInterface(const IComplexTypeInterface &&ano);
			IComplexTypeInterface &operator=(const IComplexTypeInterface &rhs);
			IComplexTypeInterface &operator=(const IComplexTypeInterface &&rhs);
		public:
			virtual ~IComplexTypeInterface(void);

		public:
			inline void setComplexType(const eComplexType type) { m_type = type; }
			inline const eComplexType getComplexType(void) const { return m_type; }

			inline void setMixed(const bool mixed) { m_mixed = mixed; }
			inline const bool getMixed(void) const { return m_mixed; }

			inline void setBaseType(const eDerivedType deriveType, const std::string &baseTypeName) { m_deriveType = deriveType; m_baseTypeName.assign(baseTypeName); }
			inline void setBaseType(const eDerivedType deriveType, const std::string &&baseTypeName) { m_deriveType = deriveType; m_baseTypeName.assign(std::move(baseTypeName)); }
			inline const eDerivedType getDeriveType(void) { return m_deriveType; }
			inline const std::string &getBaseTypeName(void) { return m_baseTypeName; }

		private:
			eComplexType m_type;

			bool m_mixed;

			eDerivedType m_deriveType;
			std::string m_baseTypeName;
		};
	};
};
