#include "SimpleTypeModel.h"
#include "XSDToken.h"

#include <boost/algorithm/string.hpp>

namespace XSDFrontend
{
	std::shared_ptr<SimpleType::StringType> SimpleTypeModel::getStringType(const std::string & typeName)
	{
		auto it(m_stringTypes.find(typeName));
		return it != m_stringTypes.cend() ? it->second : nullptr;
	}
	const std::shared_ptr<SimpleType::StringType> SimpleTypeModel::getStringType(const std::string & typeName) const
	{
		auto it(m_stringTypes.find(typeName));
		return it != m_stringTypes.cend() ? it->second : nullptr;
	}

	std::shared_ptr<SimpleType::NumberType> SimpleTypeModel::getNumberType(const std::string & typeName)
	{
		auto it(m_numberTypes.find(typeName));
		return it != m_numberTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::NumberType> SimpleTypeModel::getNumberType(const std::string & typeName) const
	{
		auto it(m_numberTypes.find(typeName));
		return it != m_numberTypes.cend() ? it->second : nullptr;
	}

	std::shared_ptr<SimpleType::DatetimeType> SimpleTypeModel::getDatetimeType(const std::string & typeName)
	{
		auto it(m_datetimeTypes.find(typeName));
		return it != m_datetimeTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::DatetimeType> SimpleTypeModel::getDatetimeType(const std::string & typeName) const
	{
		auto it(m_datetimeTypes.find(typeName));
		return it != m_datetimeTypes.cend() ? it->second : nullptr;
	}

	std::shared_ptr<SimpleType::DataType> SimpleTypeModel::getDataType(const std::string & typeName)
	{
		auto it(m_dataTypes.find(typeName));
		return it != m_dataTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::DataType> SimpleTypeModel::getDataType(const std::string & typeName) const
	{
		auto it(m_dataTypes.find(typeName));
		return it != m_dataTypes.cend() ? it->second : nullptr;
	}

	std::shared_ptr<SimpleType::ContainerType> SimpleTypeModel::getContainerType(const std::string & typeName)
	{
		auto it(m_containerTypes.find(typeName));
		return it != m_containerTypes.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<SimpleType::ContainerType> SimpleTypeModel::getContainerType(const std::string & typeName) const
	{
		auto it(m_containerTypes.find(typeName));
		return it != m_containerTypes.cend() ? it->second : nullptr;
	}

	SimpleType::ISimpleTypeInterface * SimpleTypeModel::getSimpleType(const std::string & typeName)
	{
		auto simpleTypes(getSimpleTypes());
		auto it(simpleTypes.find(typeName));
		return it != simpleTypes.cend() ? it->second : nullptr;
	}

	const SimpleType::ISimpleTypeInterface * SimpleTypeModel::getSimpleType(const std::string & typeName) const
	{
		auto simpleTypes(getSimpleTypes());
		auto it(simpleTypes.find(typeName));
		return it != simpleTypes.cend() ? it->second : nullptr;
	}

	std::map<std::string, SimpleType::ISimpleTypeInterface*> SimpleTypeModel::getSimpleTypes(void)
	{
		std::map<std::string, SimpleType::ISimpleTypeInterface *> ret;
		toSimpleTypes(ret, m_containerTypes);
		toSimpleTypes(ret, m_dataTypes);
		toSimpleTypes(ret, m_datetimeTypes);
		toSimpleTypes(ret, m_numberTypes);
		toSimpleTypes(ret, m_stringTypes);
		return ret;
	}

	const std::map<std::string, const SimpleType::ISimpleTypeInterface*> SimpleTypeModel::getSimpleTypes(void) const
	{
		std::map<std::string, const SimpleType::ISimpleTypeInterface *> ret;
		toSimpleTypes(ret, m_containerTypes);
		toSimpleTypes(ret, m_dataTypes);
		toSimpleTypes(ret, m_datetimeTypes);
		toSimpleTypes(ret, m_numberTypes);
		toSimpleTypes(ret, m_stringTypes);
		return ret;
	}

	const XSDFrontend::SimpleType::eSimpleType SimpleTypeModel::getType(const std::string & typeName) const
	{
		auto simpleTypes(getSimpleTypes());
		auto it(simpleTypes.find(typeName));

		if (it != simpleTypes.cend())
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
			(XSDFrontend::SimpleType::StringType::String2Type.left.find(baseTypeParts.back()) != XSDFrontend::SimpleType::StringType::String2Type.left.end()
				|| XSDFrontend::SimpleType::NumberType::String2Type.left.find(baseTypeParts.back()) != XSDFrontend::SimpleType::NumberType::String2Type.left.end()
				|| XSDFrontend::SimpleType::DatetimeType::String2Type.left.find(baseTypeParts.back()) != XSDFrontend::SimpleType::DatetimeType::String2Type.left.end()
				|| XSDFrontend::SimpleType::DataType::String2Type.left.find(baseTypeParts.back()) != XSDFrontend::SimpleType::DataType::String2Type.left.end());
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

	std::string SimpleTypeModel::getNewDefaultSimpleTypeName(void) const
	{
		static unsigned int defaultNameNumber(0);
		static const std::string SimpleTypeNamePrefix("simple_type_");

		do
		{
			++defaultNameNumber;
		} while (isTypeExist(SimpleTypeNamePrefix + std::to_string(defaultNameNumber)));
		
		return SimpleTypeNamePrefix + std::to_string(defaultNameNumber);
	}
};
