#pragma once

#include "XSDElementUtils.h"
#include <string>

namespace XSDFrontend
{
	namespace Attribute
	{
		class IAttributeInterface abstract : public XSDElementUtils::IXSDParentedElementInterface
		{
		public:
			enum class eAttributeType
			{
				tAttribute,
				tAnyAttribute
			};

		protected:
			IAttributeInterface(const eAttributeType type = eAttributeType::tAttribute) : IXSDParentedElementInterface(), m_type(type) {};
			IAttributeInterface(const IAttributeInterface &ano) = default;
			IAttributeInterface(IAttributeInterface &&ano) = default;
			IAttributeInterface &operator=(const IAttributeInterface &rhs) = default;
			IAttributeInterface &operator=(IAttributeInterface &&rhs) = default;
		public:
			virtual ~IAttributeInterface(void) = default;

			inline eAttributeType getAttributeType(void) const { return m_type; }

		private:
			eAttributeType m_type;
		};
	};
};
