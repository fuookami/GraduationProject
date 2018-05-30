#include "VEDADataFile.h"
#include "SSUtils/FileUtils.h"
#include "SSUtils/XSD/XSDAnalyzer.h"
#include "SSUtils/XSD/XSDNormalizer.h"
#include "CARSDK/ExperimentalDesignTable.h"

namespace VEDA
{
	const std::string VEDADataFile::Tag("veda_data");

	std::shared_ptr<VEDADataFile> VEDADataFile::generate(const std::string & url, const VEDAFile &parentFile)
	{
		std::shared_ptr<VEDADataFile> ret(new VEDADataFile(url));
		ret->init(*parentFile, SSUtils::File::getFileMainNameOfUrl(url));
		return ret;
	}

	std::shared_ptr<VEDADataFile> VEDADataFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(XSDFrontend::Token::SchemaTag()) != 1
			|| node->countChild(CARSDK::ExperimentalDesignTable::Tag) != 1)
		{
			return nullptr;
		}

		std::shared_ptr<VEDADataFile> ret(new VEDADataFile(url));
		if (!ret->init(node->getChildren()[node->findChild(IndexTag)]))
		{
			return nullptr;
		}

		XSDAnalyzer::XSDAnalyzer analyzer;
		if (!analyzer.scan(node->getChildren()[node->findChild(XSDFrontend::Token::SchemaTag())]))
		{
			return nullptr;
		}
		ret->m_model = analyzer.getModel();
		
		ret->m_data = node->getChildren()[node->findChild(CARSDK::ExperimentalDesignTable::Tag)];
		ret->m_data->removeParent();

		return ret;
	}

	VEDADataFile::VEDADataFile(const std::string & url)
		: VEDAFile(url, Type::Data)
	{
	}

	SSUtils::XML::Document VEDADataFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalize());

		XSDNormalizer::XSDNormalizer normalizer(m_model);
		if (!normalizer.normalize())
		{
			return SSUtils::XML::Document();
		}
		node->addChild(normalizer.getRoot());

		node->addChild(m_data);

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}
};
