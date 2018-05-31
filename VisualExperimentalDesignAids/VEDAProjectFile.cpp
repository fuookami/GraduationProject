#include "VEDAProcessFile.h"
#include "VEDAProjectFile.h"
#include <algorithm>

namespace VEDA
{
	const std::string VEDAProjectFile::Tag("veda_project");

	std::shared_ptr<VEDAProjectFile> VEDAProjectFile::generate(const std::string & url)
	{
		std::shared_ptr<VEDAProjectFile> ret(new VEDAProjectFile(url));
		return ret;
	}

	std::shared_ptr<VEDAProjectFile> VEDAProjectFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(VEDAPublicModelFile::Tag) > 1
			|| node->countChild(VEDAReportFile::Tag) > 1)
		{
			return false;
		}

		std::shared_ptr<VEDAProjectFile> ret(new VEDAProjectFile(url));
		auto indexNode(node->getChildren()[node->findChild(IndexTag)]);
		if (!ret->init(indexNode))
		{
			return nullptr;
		}

		int publicModelFileIndex(node->findChild(VEDAPublicModelFile::Tag));
		if (publicModelFileIndex != SSUtils::XML::Node::npos)
		{
			auto publicModelFileNode(node->getChildren()[publicModelFileIndex]);
			ret->m_publicModelFileUrl.assign(publicModelFileNode->getContent());
		}

		int reportFileIndex(node->findChild(VEDAReportFile::Tag));
		if (reportFileIndex != SSUtils::XML::Node::npos)
		{
			auto reportFileNode(node->getChildren()[reportFileIndex]);
			ret->m_reportFileUrl.assign(reportFileNode->getContent());
		}

		if (!ret->initIndex(node->getChildren()))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAProjectFile::VEDAProjectFile(const std::string & url)
		: VEDAFile(url, Type::Project)
	{
	}

	SSUtils::XML::Document VEDAProjectFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());

		if (!m_publicModelFileUrl.empty())
		{
			auto publicModelFileNode(SSUtils::XML::Node::generate(VEDAModelFile::Tag));
			publicModelFileNode->setContent(m_publicModelFileUrl);
			node->addChild(publicModelFileNode);
		}

		if (!m_reportFileUrl.empty())
		{
			auto reportFileNode(SSUtils::XML::Node::generate(VEDAReportFile::Tag));
			reportFileNode->setContent(m_reportFileUrl);
			node->addChild(reportFileNode);
		}

		auto indexFileNodes(normalizeIndexFiles());
		std::move(indexFileNodes.begin(), indexFileNodes.end(), std::back_inserter(node->getChildren()));

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}

	const std::string & VEDAProjectFile::IndexFileTag(void) const
	{
		return VEDAProcessFile::Tag;
	}
};
