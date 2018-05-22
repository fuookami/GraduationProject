#include "ComplexTypeModel.h"

namespace XSDFrontend
{
	const std::shared_ptr<ComplexType::Element> ComplexTypeModel::getGlobalElement(const std::string & name) const
	{
		auto it(m_globalElements.find(name));
		return it != m_globalElements.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<ComplexType::ElementGroup> ComplexTypeModel::getElementGroup(const std::string & name) const
	{
		auto it(m_elementGroups.find(name));
		return it != m_elementGroups.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<ComplexType::SimpleContent> ComplexTypeModel::getSimpleContent(const std::string & name) const
	{
		auto it(m_simpleContent.find(name));
		return it != m_simpleContent.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<ComplexType::ComplexContent> ComplexTypeModel::getComplexContent(const std::string & name) const
	{
		auto it(m_complexContent.find(name));
		return it != m_complexContent.cend() ? it->second : nullptr;
	}

	const ComplexType::IComplexTypeInterface * ComplexTypeModel::getComplexType(const std::string & name) const
	{
		auto complexTypes(getComplexTypes());
		auto it(complexTypes.find(name));
		return it != complexTypes.cend() ? it->second : nullptr;
	}

	std::map<std::string, ComplexType::IComplexTypeInterface*> ComplexTypeModel::getComplexTypes(void)
	{
		std::map<std::string, ComplexType::IComplexTypeInterface*> ret;
		toComplexTypes(ret, m_simpleContent);
		toComplexTypes(ret, m_complexContent);
		return ret;
	}

	const std::map<std::string, const ComplexType::IComplexTypeInterface*> ComplexTypeModel::getComplexTypes(void) const
	{
		std::map<std::string, const ComplexType::IComplexTypeInterface*> ret;
		toComplexTypes(ret, m_simpleContent);
		toComplexTypes(ret, m_complexContent);
		return ret;
	}

	std::string ComplexTypeModel::getNewDefaultElementGroupName(void) const
	{
		static unsigned int defaultNameNumber(0);
		static const std::string ElementGroupNamePrefix("element_group_");

		do
		{
			++defaultNameNumber;
		} while (isElementGroupExist(ElementGroupNamePrefix + std::to_string(defaultNameNumber)));
		
		return ElementGroupNamePrefix + std::to_string(defaultNameNumber);
	}

	std::string ComplexTypeModel::getNewDefaultComplexTypeName(void) const
	{
		static unsigned int defaultNameNumber(0);
		static const std::string ComplexTypeNamePrefix("complex_type_");

		do
		{
			++defaultNameNumber;
		} while (isElementGroupExist(ComplexTypeNamePrefix + std::to_string(defaultNameNumber)));

		return ComplexTypeNamePrefix + std::to_string(defaultNameNumber);
	}
};
