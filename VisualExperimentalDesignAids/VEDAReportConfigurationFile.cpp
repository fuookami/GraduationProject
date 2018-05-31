#include "VEDAReportConfigurationFile.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string VEDAReportConfigurationFile::Tag("veda_report_configuration");

	std::shared_ptr<VEDAReportConfigurationFile> VEDAReportConfigurationFile::generate(const std::string & url, const VEDAFile & parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::shared_ptr<VEDAReportConfigurationFile> ret(new VEDAReportConfigurationFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileMainNameOfUrl(url)))
		{
			return nullptr;
		}

		ret->m_model = model;
		return ret;
	}

	std::shared_ptr<VEDAReportConfigurationFile> VEDAReportConfigurationFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(XSDFrontend::Token::SchemaTag()) != 1)
		{
			return nullptr;
		}

		std::shared_ptr<VEDAReportConfigurationFile> ret(new VEDAReportConfigurationFile(url));
		if (!ret->init(node->getChildren()[node->findChild(IndexTag)], node->getChildren()[node->findChild(XSDFrontend::Token::SchemaTag())]))
		{
			return nullptr;
		}

		if (!ret->initIndex(node->getChildren()))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAReportConfigurationFile::VEDAReportConfigurationFile(const std::string & url)
		: VEDAModelFileBase(url, Type::ReportConfiguration)
	{
	}

	SSUtils::XML::Document VEDAReportConfigurationFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());
		node->addChild(normalizeModelParameter());

		auto indexFileNodes(normalizeIndexFiles());
		std::move(indexFileNodes.begin(), indexFileNodes.end(), std::back_inserter(node->getChildren()));

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}

	const std::string & VEDAReportConfigurationFile::IndexFileTag(void) const
	{
		return VEDAReportDataFile::Tag;
	}
};
