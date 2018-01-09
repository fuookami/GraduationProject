#pragma once

#include "Element.h"
#include "AnyElement.h"
#include "ElementGroup.h"
#include "SimpleContent.h"
#include "ComplexContent.h"

namespace XSDFrontend
{
	class ComplexTypeModel
	{
	public:
		ComplexTypeModel(void);
		ComplexTypeModel(const ComplexTypeModel &ano) = delete;
		ComplexTypeModel(const ComplexTypeModel &&ano) = delete;
		ComplexTypeModel &operator=(const ComplexTypeModel &rhs) = delete;
		ComplexTypeModel &operator=(const ComplexTypeModel &&rhs) = delete;
		~ComplexTypeModel(void);

		const std::shared_ptr<ComplexType::Element> getGlobalElement(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::Element>> &getGlobalElements(void) { return m_globalElements; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::Element>> &getGlobalElements(void) const { return m_globalElements; }

		const std::shared_ptr<ComplexType::Element> getElement(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::Element>> &getElements(void) { return m_elements; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::Element>> &getElements(void) const { return m_elements; }

		const std::shared_ptr<ComplexType::ElementGroup> getElementGroup(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::ElementGroup>> &getElementGroups(void) { return m_elementGroups; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::ElementGroup>> &getElementGroups(void) const { return m_elementGroups; }

		const std::shared_ptr<ComplexType::SimpleContent> getSimpleContent(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::SimpleContent>> &getSimpleContents(void) { return m_simpleContent; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::SimpleContent>> &getSimpleContents(void) const { return m_simpleContent; }

		const std::shared_ptr<ComplexType::ComplexContent> getComplexContent(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::ComplexContent>> &getComplexContents(void) { return m_complexContent; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::ComplexContent>> &getComplexContents(void) const { return m_complexContent; }

		const ComplexType::IComplexTypeInterface *getComplexType(const std::string &name) const;
		inline std::map<std::string, ComplexType::IComplexTypeInterface *> &getComplexTypes(void) { return m_complexTypes; }
		inline const std::map<std::string, ComplexType::IComplexTypeInterface *> &getComplexTypes(void) const { return m_complexTypes; }

		inline void clear(void) { m_globalElements.clear(); m_elementGroups.clear(); m_simpleContent.clear(); m_complexContent.clear(); m_complexTypes.clear(); }

	public:
		static const std::string getNewDefaultElementGroupName(void);
		static const std::string getNewDefaultComplexTypeName(void);

	private:
		std::map<std::string, std::shared_ptr<ComplexType::Element>> m_globalElements;
		std::map<std::string, std::shared_ptr<ComplexType::Element>> m_elements;
		std::map<std::string, std::shared_ptr<ComplexType::ElementGroup>> m_elementGroups;

		std::map<std::string, std::shared_ptr<ComplexType::SimpleContent>> m_simpleContent;
		std::map<std::string, std::shared_ptr<ComplexType::ComplexContent>> m_complexContent;
		std::map<std::string, ComplexType::IComplexTypeInterface *> m_complexTypes;
	};
};
