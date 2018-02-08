#pragma once

#include <string>
#include "XMLUtils.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDValueStatedElementInterface abstract
		{
		public:
			static const std::string NoDefaultValue;
			static const std::string &NoFixedValue;

		protected:
			IXSDValueStatedElementInterface(void);
			IXSDValueStatedElementInterface(const IXSDValueStatedElementInterface &ano) = default;
			IXSDValueStatedElementInterface(IXSDValueStatedElementInterface &&ano) = default;
			IXSDValueStatedElementInterface &operator=(const IXSDValueStatedElementInterface &rhs) = default;
			IXSDValueStatedElementInterface &operator=(IXSDValueStatedElementInterface &&rhs) = default;
		public:
			virtual ~IXSDValueStatedElementInterface(void) = default;

			const bool setDefault(const std::string &defaultValue);
			const bool setDefault(std::string &&defaultValue);
			inline const bool hasDefault(void) const { return m_hasDefault; }
			inline const bool defaultEnabled(void) const { return m_defaultEnabled; }
			inline const std::string &getDefault(const std::string &defaultValue) const { return m_default; }

			const bool setFixed(const std::string &fixedValue);
			const bool setFixed(std::string &&fixedValue);
			inline const bool hasFixed(void) const { return m_hasFixed; }
			inline const bool fixedEnabled(void) const { return m_fixedEnabled; }
			inline const std::string &getFixed(const std::string &fixedValue) const { return m_fixed; }

			const bool loadValueStatement(const XMLUtils::XMLNode &node);

		protected:
			inline void setValueStatedEnabled(const bool enabled) { setDefaultEnabled(enabled); setFixedEnabled(enabled); }
			void setDefaultEnabled(const bool enabled);
			void setFixedEnabled(const bool enabled);

		private:
			void clearDefault(void);
			void clearFixed(void);

		private:
			bool m_hasDefault;
			bool m_defaultEnabled;
			std::string m_default;

			bool m_hasFixed;
			bool m_fixedEnabled;
			std::string m_fixed;
		};
	};
};
