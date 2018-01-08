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
			IAttributeInterface(const eAttributeType type = eAttributeType::tAttribute);
			IAttributeInterface(const IAttributeInterface &ano);
			IAttributeInterface(const IAttributeInterface &&ano);
			IAttributeInterface &operator=(const IAttributeInterface &rhs);
			IAttributeInterface &operator=(const IAttributeInterface &&rhs);
		public:
			virtual ~IAttributeInterface(void);

			inline eAttributeType getAttributeType(void) const { return m_type; }

		private:
			eAttributeType m_type;
		};
	};
};
