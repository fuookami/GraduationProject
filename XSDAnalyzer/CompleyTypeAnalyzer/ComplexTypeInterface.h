#pragma once

#include "XSDElementUtils.h"

namespace XSDFrontend
{
	namespace ComplexType
	{
		class IComplexTypeInterface abstract : public XSDElementUtils::IXSDNamedElementInterface
		{
		public:
			enum class eDeriveType
			{
				tNone,
				tRestriction,
				tExtension,
			};

		protected:
			IComplexTypeInterface();
			IComplexTypeInterface(const IComplexTypeInterface &ano);
			IComplexTypeInterface(const IComplexTypeInterface &&ano);
			IComplexTypeInterface &operator=(const IComplexTypeInterface &rhs);
			IComplexTypeInterface &operator=(const IComplexTypeInterface &&rhs);
		public:
			virtual ~IComplexTypeInterface(void);

		private:
			std::string m_baseTypeName;
		};
	};
};
