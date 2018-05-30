#include "VEDAModelFile.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string VEDAModelFile::Tag("veda_model");

	std::shared_ptr<VEDAModelFile> VEDAModelFile::generate(const std::string & url, const VEDAFile & parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::shared_ptr<VEDAModelFile> ret(new VEDAModelFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileMainNameOfUrl(url)))
		{
			return nullptr;
		}

		ret->m_model = model;
		return ret;
	}

	std::shared_ptr<VEDAModelFile> VEDAModelFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(XSDFrontend::Token::SchemaTag()) != 1)
		{
			return nullptr;
		}

		std::shared_ptr<VEDAModelFile> ret(new VEDAModelFile(url));
		if (!ret->init(node->getChildren()[node->findChild(IndexTag)], node->getChildren()[node->findChild(XSDFrontend::Token::SchemaTag())]))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAModelFile::VEDAModelFile(const std::string & url)
		: VEDAModelFileBase(url, Type::Model)
	{
	}

	SSUtils::XML::Document VEDAModelFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());
		node->addChild(normalizeModelParameter());
		
		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}
};
