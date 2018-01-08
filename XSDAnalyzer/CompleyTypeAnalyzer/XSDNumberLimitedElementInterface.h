#pragma once

#include <string>

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNumberLimitedElementInterface abstract
		{
		public:
			static const std::string MaxOccursUnboundedString;
			static const int MaxOccursUnbounded = -1;

		protected:
			IXSDNumberLimitedElementInterface(const int minOccurs = 1, const int maxOccurs = 1);
			IXSDNumberLimitedElementInterface(const IXSDNumberLimitedElementInterface &ano);
			IXSDNumberLimitedElementInterface(const IXSDNumberLimitedElementInterface &&ano);
			IXSDNumberLimitedElementInterface &operator=(const IXSDNumberLimitedElementInterface &rhs);
			IXSDNumberLimitedElementInterface &operator=(const IXSDNumberLimitedElementInterface &&rhs);
		public:
			virtual ~IXSDNumberLimitedElementInterface(void);

			const bool setMinOccurs(const int newMinOccurs);
			inline const int getMinOccurs(void) const { return m_minOccurs; }

			const bool setMaxOccurs(const int newMaxOccurs);
			inline const int getMaxOccurs(void) const { return m_maxOccurs; }

		private:
			int m_minOccurs;
			int m_maxOccurs;
		};
	}
};
