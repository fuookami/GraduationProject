#include "VEDAProject.h"
#include "VEDAProcess.h"
#include "VEDAGlobal.h"

namespace VEDA
{
	const SSUtils::uint32 VEDAProject::KeyLength = 128;

	std::shared_ptr<VEDAProject> VEDAProject::generate(const std::string & name)
	{
		return std::shared_ptr<VEDAProject>(new VEDAProject(name));
	}

	std::shared_ptr<VEDAProject> VEDAProject::generate(std::string && name)
	{
		return std::shared_ptr<VEDAProject>(new VEDAProject(std::move(name)));
	}

	VEDAProject::VEDAProject(const std::string &name)
		: m_name(name)
	{
		init();
	}

	VEDAProject::VEDAProject(std::string &&name)
		: m_name(std::move(name))
	{
		init();
	}

	SSUtils::XML::Document VEDAProject::toXML(void)
	{
		auto root(SSUtils::XML::Node::generate(Tags::Project));

		auto nameNode(SSUtils::XML::Node::generate(Tags::Name));
		nameNode->setContent(m_name);
		root->addChild(nameNode);

		auto publicKeyNode(SSUtils::XML::Node::generate(Tags::VerificationPublicKey));
		publicKeyNode->setContent(m_verifier.publicKey);
		root->addChild(publicKeyNode);

		auto privateKeyNode(SSUtils::XML::Node::generate(Tags::VerificationPrivateKey));
		privateKeyNode->setContent(m_signer.privateKey);
		root->addChild(privateKeyNode);

		auto verificationTokenNode(SSUtils::XML::Node::generate(Tags::VerificationToken));
		verificationTokenNode->addAttr(Attrs::Type, std::string("base64"));
		verificationTokenNode->setContent(SSUtils::Data::toBase64String(m_verificationToken));
		root->addChild(verificationTokenNode);

		// to do
		/*
		for (const auto process : m_processes)
		{
		}
		*/

		SSUtils::XML::Document doc;
		doc.getRoots().push_back(root);
		return doc;
	}

	std::shared_ptr<VEDAProject> VEDAProject::fromXML(const SSUtils::XML::Document & doc)
	{
		return std::shared_ptr<VEDAProject>();
	}
};
