#pragma once

#include "XMLUtils.h"
#include "XSDElementUtils.h"
#include "SimpleTypeValueLimitConfiguration.h"
#include "SimpleTypeValueEnumrationConfiguration.h"
#include "SimpleTypeLengthLimitConfiguration.h"

#include <string>
#include <boost/bimap.hpp>

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

		class SSXSDUtils_API_DECLSPEC ISimpleTypeInterface abstract : public XSDElementUtils::IXSDNamedElementInterface,
			public XSDElementUtils::IXSDExtraAttributeInterface
		{
		public:
			enum class eWhiteSpace
			{
				Preserve,
				Replace,
				Collapse
			};
			static const boost::bimap<std::string, ISimpleTypeInterface::eWhiteSpace> String2WhiteSpace;
			static const std::set<std::string> BaseAttrs;
			static const eWhiteSpace DefaultWhiteSpace = eWhiteSpace::Preserve;

		protected:
			ISimpleTypeInterface(const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = DefaultWhiteSpace);
			ISimpleTypeInterface(const std::string &name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = DefaultWhiteSpace);
			ISimpleTypeInterface(std::string &&name, const eSimpleType type = eSimpleType::tStringType, const eWhiteSpace whitSpace = DefaultWhiteSpace);
			ISimpleTypeInterface(const ISimpleTypeInterface &ano) = default;
			ISimpleTypeInterface(ISimpleTypeInterface &&ano) = default;
			ISimpleTypeInterface &operator=(const ISimpleTypeInterface &rhs) = default;
			ISimpleTypeInterface &operator=(ISimpleTypeInterface &&rhs) = default;

		public:
			virtual ~ISimpleTypeInterface(void) = default;

		public:
			virtual const bool refreshValidator(const std::shared_ptr<SSUtils::XML::Node> node) = 0;
			virtual std::set<std::string> suppliedTokens(void) const;
			virtual std::set<std::string> neededTokens(void) const;
			virtual std::shared_ptr<SSUtils::XML::Node> saveValidator(const std::shared_ptr<SSUtils::XML::Node> root) const;

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
