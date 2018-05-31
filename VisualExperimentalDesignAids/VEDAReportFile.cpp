#include "VEDAReportFile.h"
#include "SSUtils/FileUtils.h"
#include <algorithm>

namespace VEDA
{
	const std::string VEDAReportFile::Tag("veda_report");

	std::shared_ptr<VEDAReportFile> VEDAReportFile::generate(const std::string & url, const VEDAFile & parentFile)
	{
		std::shared_ptr<VEDAReportFile> ret(new VEDAReportFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileNameOfUrl(url)))
		{
			return nullptr;
		}

		return ret;
	}

	std::shared_ptr<VEDAReportFile> VEDAReportFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1)
		{
			return false;
		}

		std::shared_ptr<VEDAReportFile> ret(new VEDAReportFile(url));
		auto indexNode(node->getChildren()[node->findChild(IndexTag)]);
		if (!ret->init(indexNode))
		{
			return nullptr;
		}

		if (!ret->initIndex(node->getChildren()))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAReportFile::VEDAReportFile(const std::string & url)
		: VEDAFile(url, Type::Report)
	{
	}
	
	SSUtils::XML::Document VEDAReportFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());

		auto indexFileNodes(normalizeIndexFiles());
		std::move(indexFileNodes.begin(), indexFileNodes.end(), std::back_inserter(node->getChildren()));

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}

	const std::string & VEDAReportFile::IndexFileTag(void) const
	{
		return VEDAReportConfigurationFile::Tag;
	}
};
