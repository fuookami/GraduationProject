#include "VEDAOperationFile.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string VEDAOperationFile::Tag("veda_operation");
	const std::string VEDAOperationFile::MethodTag("experimental_design_method");
	const std::string VEDAOperationFile::MethodNameTag("name");
	const std::string VEDAOperationFile::MethodCategoryTag("category");
	const std::string VEDAOperationFile::MethodAttributeTag("attribute");

	std::shared_ptr<VEDAOperationFile> VEDAOperationFile::generate(const std::string & url, const VEDAFile & parentFile, const std::string & designMethodName, const std::string & designMethodCategory, const std::map<std::string, std::string>& attrs)
	{
		std::shared_ptr<VEDAOperationFile> ret(new VEDAOperationFile(url));
		ret->init(parentFile, SSUtils::File::getFileNameOfUrl(url));

		ret->m_designMethodName.assign(designMethodName);
		ret->m_designMethodCategory.assign(designMethodCategory);
		ret->m_attrs = attrs;

		return ret;
	}

	std::shared_ptr<VEDAOperationFile> VEDAOperationFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(MethodTag) != 1)
		{
			return false;
		}

		auto indexNode(node->getChildren()[node->findChild(IndexTag)]);
		auto methodNode(node->getChildren()[node->findChild(MethodTag)]);

		if (indexNode->countChild(MethodNameTag) != 1
			|| indexNode->countChild(MethodCategoryTag) != 1
			|| indexNode->countChild(MethodAttributeTag) != 1)
		{
			return false;
		}

		std::shared_ptr<VEDAOperationFile> ret(new VEDAOperationFile(url));
		ret->init(indexNode);

		ret->m_designMethodName.assign(methodNode->getChildren()[methodNode->findChild(MethodNameTag)]->getContent());
		ret->m_designMethodCategory.assign(methodNode->getChildren()[methodNode->findChild(MethodCategoryTag)]->getContent());
		ret->m_attrs = methodNode->getChildren()[methodNode->findChild(MethodAttributeTag)]->getAttrs();

		for (const auto child : node->getChildren())
		{
			if (child->getTag() == VEDADataFile::Tag)
			{
				ret->m_dataFiles.insert(child->getContent());
			}
		}

		return ret;
	}

	VEDA::VEDAOperationFile::VEDAOperationFile(const std::string & url)
		: VEDAFile(url, Type::Operation)
	{
	}

	SSUtils::XML::Document VEDAOperationFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());
		node->addChild(normalizeExperimentalDesignMethodParameter());
		
		for (const auto &url : m_dataFiles)
		{
			auto dataFileNode(SSUtils::XML::Node::generate(VEDADataFile::Tag));
			dataFileNode->setContent(url);
			node->addChild(dataFileNode);
		}

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}

	std::shared_ptr<SSUtils::XML::Node> VEDAOperationFile::normalizeExperimentalDesignMethodParameter(void) const
	{
		auto node(SSUtils::XML::Node::generate(MethodTag));
		auto nameNode(SSUtils::XML::Node::generate(MethodNameTag));
		auto categoryNode(SSUtils::XML::Node::generate(MethodCategoryTag));
		auto attributeNode(SSUtils::XML::Node::generate(MethodAttributeTag));

		nameNode->setContent(m_designMethodName);
		categoryNode->setContent(m_designMethodCategory);
		attributeNode->getAttrs() = m_attrs;

		node->addChild(nameNode);
		node->addChild(categoryNode);
		node->addChild(attributeNode);
		return node;
	}
};
