#pragma once

#include "Element.h"
#include "AnyElement.h"
#include "ElementGroup.h"
#include "SimpleContent.h"
#include "ComplexContent.h"

namespace XSDFrontend
{
	class SSXSDUtils_API_DECLSPEC ComplexTypeModel
	{
	public:
		ComplexTypeModel(void) = default;
		ComplexTypeModel(const ComplexTypeModel &ano) = delete;
		ComplexTypeModel(ComplexTypeModel &&ano) = delete;
		ComplexTypeModel &operator=(const ComplexTypeModel &rhs) = delete;
		ComplexTypeModel &operator=(ComplexTypeModel &&rhs) = delete;
		~ComplexTypeModel(void) = default;

		const std::shared_ptr<ComplexType::Element> getGlobalElement(const std::string &name) const;
		inline std::map<std::string, std::shared_ptr<ComplexType::Element>> &getGlobalElements(void) { return m_globalElements; }
		inline const std::map<std::string, std::shared_ptr<ComplexType::Element>> &getGlobalElements(void) const { return m_globalElements; }

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
		std::map<std::string, ComplexType::IComplexTypeInterface *> getComplexTypes(void);
		const std::map<std::string, const ComplexType::IComplexTypeInterface *> getComplexTypes(void) const;

		inline const bool isGlobalElementExist(const std::string &name) const { return m_globalElements.find(name) != m_globalElements.cend(); }
		inline const bool isElementGroupExist(const std::string &name) const { return m_elementGroups.find(name) != m_elementGroups.cend(); }

		inline const bool isComplexTypeExist(const std::string &name) const { return isSimpleContent(name) || isComplexContent(name); }
		inline const bool isSimpleContent(const std::string &name) const { return m_simpleContent.find(name) != m_simpleContent.cend(); }
		inline const bool isComplexContent(const std::string &name) const { return m_complexContent.find(name) != m_complexContent.cend(); }

		inline const bool hasToken(const std::string &token) const { return isGlobalElementExist(token) || isElementGroupExist(token) || isComplexTypeExist(token); }
		inline void clear(void) { m_globalElements.clear(); m_elementGroups.clear(); m_simpleContent.clear(); m_complexContent.clear(); }

	public:
		std::string getNewDefaultElementGroupName(void) const;
		std::string getNewDefaultComplexTypeName(void) const;

	private:
		template<typename T>
		static void toComplexTypes(std::map<std::string, ComplexType::IComplexTypeInterface *> &ret, const std::map<std::string, std::shared_ptr<T>> &types)
		{
			for (const auto &pair : types)
			{
				ret.insert(std::make_pair(pair.first, dynamic_cast<ComplexType::IComplexTypeInterface *>(pair.second.get())));
			}
		}

		template<typename T>
		static void toComplexTypes(std::map<std::string, const ComplexType::IComplexTypeInterface *> &ret, const std::map<std::string, std::shared_ptr<T>> &types)
		{
			for (const auto &pair : types)
			{
				ret.insert(std::make_pair(pair.first, dynamic_cast<const ComplexType::IComplexTypeInterface *>(pair.second.get())));
			}
		}

	private:
		std::map<std::string, std::shared_ptr<ComplexType::Element>> m_globalElements;
		std::map<std::string, std::shared_ptr<ComplexType::ElementGroup>> m_elementGroups;

		std::map<std::string, std::shared_ptr<ComplexType::SimpleContent>> m_simpleContent;
		std::map<std::string, std::shared_ptr<ComplexType::ComplexContent>> m_complexContent;
	};
};
