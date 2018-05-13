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
			IElementInterface(const eElementType type = eElementType::tElement) : IXSDParentedElementInterface(), IXSDNumberLimitedElementInterface(), m_type(type) {};
			IElementInterface(const IElementInterface &ano) = default;
			IElementInterface(IElementInterface &&ano) = default;
			IElementInterface &operator=(const IElementInterface &rhs) = default;
			IElementInterface &operator=(IElementInterface &&rhs) = default;
		public:
			virtual ~IElementInterface(void) = default;

			inline const eElementType getElementType(void) const { return m_type; }

		private:
			eElementType m_type;
		};
	};
};
