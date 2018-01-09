#include "ComplexTypeModel.h"

namespace XSDFrontend
{
	XSDFrontend::ComplexTypeModel::ComplexTypeModel(void)
		: m_globalElements(), m_elementGroups(), m_simpleContent(), m_complexContent(), m_complexTypes()
	{
	}

	XSDFrontend::ComplexTypeModel::~ComplexTypeModel(void)
	{
	}

	const std::shared_ptr<ComplexType::Element> ComplexTypeModel::getGlobalElement(const std::string & name) const
	{
		auto it(m_globalElements.find(name));
		return it != m_globalElements.cend() ? it->second : nullptr;
	}

	const std::shared_ptr<ComplexType::Element> ComplexTypeModel::getElement(const std::string & name) const
	{
		auto it(m_elements.find(name));
		return it != m_elements.cend() ? it->second : nullptr;
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
		auto it(m_complexTypes.find(name));
		return it != m_complexTypes.cend() ? it->second : nullptr;
	}

	const std::string ComplexTypeModel::getNewDefaultElementGroupName(void)
	{
		static unsigned int defaultNameNumber(0);
		static const std::string SimpleTypeNamePrefix("element_group_");

		++defaultNameNumber;
		return SimpleTypeNamePrefix + std::to_string(defaultNameNumber);
	}

	const std::string ComplexTypeModel::getNewDefaultComplexTypeName(void)
	{
		static unsigned int defaultNameNumber(0);
		static const std::string SimpleTypeNamePrefix("complex_type_");

		++defaultNameNumber;
		return SimpleTypeNamePrefix + std::to_string(defaultNameNumber);
	}
};
