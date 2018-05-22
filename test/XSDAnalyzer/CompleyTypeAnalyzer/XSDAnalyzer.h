#pragma once

#include "SimpleTypeAnalyzer.h"
#include "AttributeAnalyzer.h"
#include "ComplexTypeAnalyzer.h"
#include "XSDModel.h"

#include <set>

namespace XSDAnalyzer
{
	class XSDAnalyzer
	{
	public:
		XSDAnalyzer(void);
		XSDAnalyzer(const XSDAnalyzer &ano) = delete;
		XSDAnalyzer(XSDAnalyzer &&ano) = delete;
		XSDAnalyzer &operator=(const XSDAnalyzer &rhs) = delete;
		XSDAnalyzer &operator=(XSDAnalyzer &&rhs) = delete;
		~XSDAnalyzer(void) = default;

		const bool scan(const std::string &fileUrl, const SSUtils::CharType charType);

		inline const std::shared_ptr<XSDFrontend::XSDModel> getModel(void) const { return m_xsdModel; }

	private:
		const bool scanIncludeTag(const std::string &fileName, const std::string &filePath, const std::shared_ptr<SSUtils::XML::Node> node, const SSUtils::CharType charType);
		
		std::vector<std::set<int>> generateTopologicalTable(const std::shared_ptr<SSUtils::XML::Node> root);

	private:
		std::set<std::string> m_scanedFiles;

		std::shared_ptr<XSDFrontend::XSDModel> m_xsdModel;

		SimpleTypeAnalyzer m_simpleTypeAnalyzer;
		AttributeAnalyzer m_attributeAnalyzer;
		ComplexTypeAnalyzer m_complexTypeAnalyzer;
	};
};
