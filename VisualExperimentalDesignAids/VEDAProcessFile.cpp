#include "VEDAProcessFile.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string VEDAProcessFile::Tag("veda_process");

	std::shared_ptr<VEDAProcessFile> VEDAProcessFile::generate(const std::string & url, const VEDAFile & parentFile)
	{
		std::shared_ptr<VEDAProcessFile> ret(new VEDAProcessFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileNameOfUrl(url)))
		{
			return nullptr;
		}

		return ret;
	}

	std::shared_ptr<VEDAProcessFile> VEDAProcessFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1 
			|| node->countChild(VEDAModelFile::Tag) > 1)
		{
			return false;
		}

		std::shared_ptr<VEDAProcessFile> ret(new VEDAProcessFile(url));
		auto indexNode(node->getChildren()[node->findChild(IndexTag)]);
		if (!ret->init(indexNode))
		{
			return nullptr;
		}

		int modelFileIndex(node->findChild(VEDAModelFile::Tag));
		if (modelFileIndex != SSUtils::XML::Node::npos)
		{
			auto modelFileNode(node->getChildren()[modelFileIndex]);
			ret->m_modelFileUrl.assign(modelFileNode->getContent());
		}

		if (!ret->initIndex(node->getChildren()))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAProcessFile::VEDAProcessFile(const std::string & url)
		: VEDAFile(url, Type::Process)
	{
	}

	SSUtils::XML::Document VEDAProcessFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());
		
		if (!m_modelFileUrl.empty())
		{
			auto modelFileNode(SSUtils::XML::Node::generate(VEDAModelFile::Tag));
			modelFileNode->setContent(m_modelFileUrl);
			node->addChild(modelFileNode);
		}

		auto indexFileNodes(normalizeIndexFiles());
		std::move(indexFileNodes.begin(), indexFileNodes.end(), std::back_inserter(node->getChildren()));

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}

	const std::string & VEDAProcessFile::IndexFileTag(void) const
	{
		return VEDAOperationFile::Tag;
	}
};
