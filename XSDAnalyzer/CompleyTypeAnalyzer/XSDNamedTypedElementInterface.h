#pragma once

#include "XSDNamedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNamedTypedElementInterface abstract : public IXSDNamedElementInterface
		{
		protected:
			IXSDNamedTypedElementInterface(void);
			IXSDNamedTypedElementInterface(const std::string &name);
			IXSDNamedTypedElementInterface(const std::string &&name);
			IXSDNamedTypedElementInterface(const std::string &name, const std::string &type);
			IXSDNamedTypedElementInterface(const std::string &name, const std::string &&type);
			IXSDNamedTypedElementInterface(const std::string &&name, const std::string &type);
			IXSDNamedTypedElementInterface(const std::string &&name, const std::string &&type);
			IXSDNamedTypedElementInterface(const IXSDNamedTypedElementInterface &ano);
			IXSDNamedTypedElementInterface(const IXSDNamedTypedElementInterface &&ano);
			IXSDNamedTypedElementInterface &operator=(const IXSDNamedTypedElementInterface &rhs);
			IXSDNamedTypedElementInterface &operator=(const IXSDNamedTypedElementInterface &&rhs);
		public:
			virtual ~IXSDNamedTypedElementInterface(void);

		public:
			inline void setType(const std::string &type) { m_type.assign(type); }
			inline void setType(const std::string &&type) { m_type.assign(std::move(type)); }
			inline const std::string &getType(void) const { return m_type; }

		private:
			std::string m_type;
		};
	};
};
