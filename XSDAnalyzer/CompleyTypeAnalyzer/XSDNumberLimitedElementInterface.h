#pragma once

#include <string>
#include <cstdint>
#include "XMLUtils.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNumberLimitedElementInterface abstract
		{
		public:
			static const std::string MaxOccursUnboundedString;
			static const unsigned int MaxOccursUnbounded = UINT_FAST32_MAX;

		protected:
			IXSDNumberLimitedElementInterface(const int minOccurs = 1, const int maxOccurs = 1);
			IXSDNumberLimitedElementInterface(const IXSDNumberLimitedElementInterface &ano) = default;
			IXSDNumberLimitedElementInterface(IXSDNumberLimitedElementInterface &&ano) = default;
			IXSDNumberLimitedElementInterface &operator=(const IXSDNumberLimitedElementInterface &rhs) = default;
			IXSDNumberLimitedElementInterface &operator=(IXSDNumberLimitedElementInterface &&rhs) = default;
		public:
			virtual ~IXSDNumberLimitedElementInterface(void) = default;

			const bool setMinOccurs(const unsigned int newMinOccurs);
			inline const unsigned int getMinOccurs(void) const { return m_minOccurs; }

			const bool setMaxOccurs(const unsigned int newMaxOccurs);
			inline const unsigned int getMaxOccurs(void) const { return m_maxOccurs; }

			const bool loadNumberLimitation(const std::shared_ptr<SSUtils::XML::Node> &node);

		private:
			unsigned int m_minOccurs;
			unsigned int m_maxOccurs;
		};
	}
};
