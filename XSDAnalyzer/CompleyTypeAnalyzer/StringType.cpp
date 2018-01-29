#include "StringType.h"

namespace XSDFrontend
{
	namespace SimpleType
	{
		StringType::StringType(void)
			: StringType("")
		{
		}

		StringType::StringType(const std::string & name, const eBaseType baseType)
			: ISimpleTypeInterface(name, eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(), 
			m_baseType(baseType), m_pattern()
		{
		}

		StringType::StringType(std::string && name, const eBaseType baseType)
			: ISimpleTypeInterface(std::move(name), eSimpleType::tStringType), LengthLimitConfiguration(), ValueEnumrationConfiguration(),
			m_baseType(baseType), m_pattern()
		{
		}

		void StringType::refreshValidator(const XMLUtils::XMLNode & node)
		{
			//! to do
		}
	};
};
