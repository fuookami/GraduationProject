#pragma once

#include "XSDNamedElementInterface.h"

namespace XSDFrontend
{
	namespace XSDElementUtils
	{
		class IXSDNamedTypedElementInterface abstract : public IXSDNamedElementInterface
		{
		protected:
			IXSDNamedTypedElementInterface(void) = default;
			IXSDNamedTypedElementInterface(const std::string &name);
			IXSDNamedTypedElementInterface(std::string &&name);
			IXSDNamedTypedElementInterface(const std::string &name, const std::string &type);
			IXSDNamedTypedElementInterface(const std::string &name, std::string &&type);
			IXSDNamedTypedElementInterface(std::string &&name, const std::string &type);
			IXSDNamedTypedElementInterface(std::string &&name, std::string &&type);
			IXSDNamedTypedElementInterface(const IXSDNamedTypedElementInterface &ano) = default;
			IXSDNamedTypedElementInterface(IXSDNamedTypedElementInterface &&ano) = default;
			IXSDNamedTypedElementInterface &operator=(const IXSDNamedTypedElementInterface &rhs) = default;
			IXSDNamedTypedElementInterface &operator=(IXSDNamedTypedElementInterface &&rhs) = default;
		public:
			virtual ~IXSDNamedTypedElementInterface(void) = default;

		public:
			inline void setType(const std::string &type) { m_type.assign(type); }
			inline void setType(const std::string &&type) { m_type.assign(std::move(type)); }
			inline const std::string &getType(void) const { return m_type; }

		private:
			std::string m_type;
		};
	};
};
