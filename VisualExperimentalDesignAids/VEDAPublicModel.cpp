#include "VEDAPublicModelFile.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const std::string VEDAPublicModelFile::Tag("veda_model");

	std::shared_ptr<VEDAPublicModelFile> VEDAPublicModelFile::generate(const std::string & url, const VEDAFile & parentFile, const std::shared_ptr<XSDFrontend::XSDModel> model)
	{
		std::shared_ptr<VEDAPublicModelFile> ret(new VEDAPublicModelFile(url));
		if (!ret->init(parentFile, SSUtils::File::getFileMainNameOfUrl(url)))
		{
			return nullptr;
		}

		ret->m_model = model;
		return ret;
	}

	std::shared_ptr<VEDAPublicModelFile> VEDAPublicModelFile::generate(const std::string & url, const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != Tag
			|| node->countChild(IndexTag) != 1
			|| node->countChild(XSDFrontend::Token::SchemaTag()) != 1)
		{
			return nullptr;
		}

		std::shared_ptr<VEDAPublicModelFile> ret(new VEDAPublicModelFile(url));
		if (!ret->init(node->getChildren()[node->findChild(IndexTag)], node->getChildren()[node->findChild(XSDFrontend::Token::SchemaTag())]))
		{
			return nullptr;
		}

		return ret;
	}

	VEDAPublicModelFile::VEDAPublicModelFile(const std::string & url)
		: VEDAModelFileBase(url, Type::PublicModel)
	{
	}

	SSUtils::XML::Document VEDAPublicModelFile::toXML(void) const
	{
		auto node(SSUtils::XML::Node::generate(Tag));
		node->addChild(normalizeIndexParameter());
		node->addChild(normalizeModelParameter());

		SSUtils::XML::Document doc;
		doc.push_back(node);
		return doc;
	}
};
