#pragma once

#include "XMLUtils.h"
#include "XSDElementUtils.h"
#include "SimpleTypeValueLimitConfiguration.h"
#include "SimpleTypeValueEnumrationConfiguration.h"
#include "SimpleTypeLengthLimitConfiguration.h"

#include <string>

namespace XSDFrontend
{
	namespace SimpleType
	{
		enum class eSimpleType
		{
			tStringType,
			tNumberType,
			tDatetimeType,
			tDataType,
			tContainerType,
			tNonExist
		};

		class ISimpleTypeInterface abstract : public XSDElementUtils::IXSDNamedElementInterface
		{
		public:
			enum class eWhiteSpace
			{
				Preserve,
				Replace,
				Collapse
			};
			static const std::map<std::string, ISimpleTypeInterface::eWhiteSpace> String2WhiteSpace;

		protected:
			ISimpleTypeInterface(const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(const std::string &name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(std::string &&name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = eWhiteSpace::Preserve);
			ISimpleTypeInterface(const ISimpleTypeInterface &ano) = default;
			ISimpleTypeInterface(ISimpleTypeInterface &&ano) = default;
			ISimpleTypeInterface &operator=(const ISimpleTypeInterface &rhs) = default;
			ISimpleTypeInterface &operator=(ISimpleTypeInterface &&rhs) = default;

		public:
			virtual ~ISimpleTypeInterface(void) = default;

		public:
			virtual const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) = 0;

			inline void setSimpleType(const eSimpleType type) { m_type = type; }
			inline const eSimpleType getSimpleType(void) const { return m_type; }

			inline void setWhiteSpace(const eWhiteSpace whiteSpace) { m_whiteSpace = whiteSpace; }
			inline const eWhiteSpace getWhiteSpace(void) const { return m_whiteSpace; }

			inline void setBaseTypeName(const std::string &baseTypeName) { m_baseTypeName.assign(baseTypeName); }
			inline const std::string &getBaseTypeName(void) const { return m_baseTypeName; }

		private:
			eSimpleType m_type;
			eWhiteSpace m_whiteSpace;

			std::string m_baseTypeName;
		};
	}
};
