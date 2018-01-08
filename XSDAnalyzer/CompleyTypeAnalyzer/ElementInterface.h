#pragma once

#include "XSDElementUtils.h"
#include <string>

namespace XSDFrontend
{
	namespace ComplexType
	{
		class IElementInterface abstract : public XSDElementUtils::IXSDParentedElementInterface,
			public XSDElementUtils::IXSDNumberLimitedElementInterface
		{
		public:
			enum class eElementType
			{
				tElement,
				tAnyElement
			};

		protected:
			IElementInterface(const eElementType type = eElementType::tElement);
			IElementInterface(const IElementInterface &ano);
			IElementInterface(const IElementInterface &&ano);
			IElementInterface &operator=(const IElementInterface &rhs);
			IElementInterface &operator=(const IElementInterface &&rhs);
		public:
			virtual ~IElementInterface(void);

			inline eElementType getElementType(void) const { return m_type; }

		private:
			eElementType m_type;
		};
	};
};
