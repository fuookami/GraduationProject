#include "SimpleTypeModel.h"
#include "XSDToken.h"

#include <boost/algorithm/string.hpp>

namespace XSDFrontend
{
	const std::shared_ptr<SimpleType::StringType> SimpleTypeModel::getStringType(const std::string & typeName) const
	{
		auto it(m_stringTypes.find(typeName));
		return it != m_stringTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::NumberType> SimpleTypeModel::getNumberType(const std::string & typeName) const
	{
		auto it(m_numberTypes.find(typeName));
		return it != m_numberTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::DatetimeType> SimpleTypeModel::getDatetimeType(const std::string & typeName) const
	{
		auto it(m_datetimeTypes.find(typeName));
		return it != m_datetimeTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::DataType> SimpleTypeModel::getDataType(const std::string & typeName) const
	{
		auto it(m_dataTypes.find(typeName));
		return it != m_dataTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::ContainerType> SimpleTypeModel::getContainerType(const std::string & typeName) const
	{
		auto it(m_containerTypes.find(typeName));
		return it != m_containerTypes.cend() ? it->second : nullptr;
	}

	const SimpleType::ISimpleTypeInterface * SimpleTypeModel::getSimpleType(const std::string & typeName) const
	{
		auto it(m_simpleTypes.find(typeName));
		return it != m_simpleTypes.cend() ? it->second : nullptr;
	}

	const XSDFrontend::SimpleType::eSimpleType SimpleTypeModel::getType(const std::string & typeName) const
	{
		auto it(m_simpleTypes.find(typeName));

		if (it != m_simpleTypes.cend())
		{
			return it->second->getSimpleType();
		}
		else
		{
			return XSDFrontend::SimpleType::eSimpleType::tNonExist;
		}
	}

	const bool SimpleTypeModel::isBaseType(const std::string & typeName)
	{
		if (!XSDFrontend::Token::isInXSDNameSpace(typeName))
		{
			return false;
		}

		std::vector<std::string> baseTypeParts;
		boost::split(baseTypeParts, typeName, boost::is_any_of(XSDFrontend::Token::NamespaceSeparator));

		return baseTypeParts.size() != 2 ? false :
			(XSDFrontend::SimpleType::StringBaseTypeName2Type.find(baseTypeParts.back()) != XSDFrontend::SimpleType::StringBaseTypeName2Type.cend()
				|| XSDFrontend::SimpleType::NumberBaseTypeName2Type.find(baseTypeParts.back()) != XSDFrontend::SimpleType::NumberBaseTypeName2Type.cend()
				|| XSDFrontend::SimpleType::DatetimeBaseTypeName2Type.find(baseTypeParts.back()) != XSDFrontend::SimpleType::DatetimeBaseTypeName2Type.cend()
				|| XSDFrontend::SimpleType::DataBaseTypeName2Type.find(baseTypeParts.back()) != XSDFrontend::SimpleType::DataBaseTypeName2Type.cend());
	}

	void SimpleTypeModel::checkAndEraseIlegalTypeInContainer(std::shared_ptr<XSDFrontend::SimpleType::ContainerType> type)
	{
		std::vector<std::string> ilegalTypeNames;
		for (const std::string &typeName : type->getBaseTypes())
		{
			if (!isTypeExist(typeName))
			{
				ilegalTypeNames.push_back(typeName);
			}
		}

		for (const std::string &ilegalTypeName : ilegalTypeNames)
		{
			type->eraseBaseType(ilegalTypeName);
		}
	}

	const std::string SimpleTypeModel::getNewDefaultName(void)
	{
		static unsigned int defaultNameNumber(0);
		static const std::string SimpleTypeNamePrefix("simple_type_");

		++defaultNameNumber;
		return SimpleTypeNamePrefix + std::to_string(defaultNameNumber);
	}
};
