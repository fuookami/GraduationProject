#include "stdafx.h"
#include "XSDModel.h"
#include "XSDNormalizer.h"
#include "XSDAnalyzer.h"

namespace XSDFrontend
{
	const std::shared_ptr<XSDModel> XSDModel::generateNewXSDModel(void)
	{
		return std::shared_ptr<XSDModel>(new XSDModel());
	}

	const std::shared_ptr<XSDModel> XSDModel::copyXSDModel(const std::shared_ptr<XSDModel> model)
	{
		XSDNormalizer::XSDNormalizer normalizer(model);
		if (!normalizer.normalize())
		{
			return nullptr;
		}
		auto xml(normalizer.getRoot());

		XSDAnalyzer::XSDAnalyzer analyzer;
		if (!analyzer.scan(xml))
		{
			return nullptr;
		}
		return analyzer.getModel();
	}

	XSDModel::XSDModel(void)
		: m_simpleTypeModel(new SimpleTypeModel()), m_attributeModel(new AttributeModel()), m_complexTypeMode(new ComplexTypeModel())
	{
	}

	std::shared_ptr<SSUtils::XML::Node> XSDModel::generateXSDRoot(void)
	{
		static const std::map<std::string ,std::string> SchemeNodeAttrs = 
		{
			std::make_pair(std::string("xmlns:xs"), std::string("http://www.w3.org/2001/XMLSchema")),
			std::make_pair(std::string("version"), std::string("3.1"))
		};

		auto ret(SSUtils::XML::Node::generate(XSDFrontend::Token::SchemaTag()));
		if (!m_description.empty())
		{
			auto annotation(SSUtils::XML::Node::generate(XSDFrontend::Token::AnnotationTag()));
			auto documentation(SSUtils::XML::Node::generate(XSDFrontend::Token::DocumentationTag()));

			documentation->addAttr(XSDFrontend::Token::LangAttr(), getDescriptionLang());
			documentation->setContent(getDescription());
			annotation->addChild(documentation);
			ret->addChild(annotation);
		}

		for (const auto &pair : SchemeNodeAttrs)
		{
			ret->addAttr(pair);
		}

		return ret;
	}
};
