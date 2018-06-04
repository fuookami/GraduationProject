#include "VEDADataFile.h"
#include "SSUtils/FileUtils.h"
#include "SSUtils/XSD/XSDAnalyzer.h"
#include "SSUtils/XSD/XSDNormalizer.h"
#include "CARSDK/ExperimentalDesignTable.h"

namespace VEDA
{
	const std::string VEDADataFile::Tag("veda_data");

	std::shared_ptr<VEDADataFile> VEDADataFile::generate(const std::string & url, const VEDAFile &parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model, const std::shared_ptr<SSUtils::XML::Node> data)
	{
		std::shared_ptr<VEDADataFile> ret(new VEDADataFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileMainNameOfUrl(url)))
		{
			return nullptr;
		}
		ret->m_model = model;
		ret->m_data = data;
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
		if (!ret->init(node->getChildren()[node->findChild(IndexTag)], node->getChildren()[node->findChild(XSDFrontend::Token::SchemaTag())], node->getChildren()[node->findChild(CARSDK::ExperimentalDesignTable::Tag)]))
		{
			return nullptr;
		}

		return ret;
	}

	VEDADataFile::VEDADataFile(const std::string & url)
		: VEDADataFileBase(url, Type::Data)
	{
	}

	SSUtils::XML::Document VEDADataFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());

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

	const std::string & VEDADataFile::DataNodeTag(void) const
	{
		return CARSDK::ExperimentalDesignTable::Tag;
	}
};
