#include "VEDAFile.h"
#include "VEDAGlobal.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	const boost::bimap<std::string, VEDAFile::Type> VEDAFile::Extension2Type =
		[]()
	{
		typedef boost::bimap<std::string, VEDAFile::Type> result_type;
		typedef result_type::value_type pair_type;

		result_type ret;
		ret.insert(pair_type(ProjectFileExtension, Type::Project));
		ret.insert(pair_type(ProcessFileExtension, Type::Process));
		ret.insert(pair_type(OperationFileExtension, Type::Operation));
		ret.insert(pair_type(ModelFileExtension, Type::Model));
		ret.insert(pair_type(DataFileExtension, Type::Data));
		ret.insert(pair_type(ReportFileExtensionl, Type::Data));
		ret.insert(pair_type(ReportConfigurationFileExtension, Type::ReportConfiguration));
		ret.insert(pair_type(ReportDataFileExtension, Type::ReportData));
		return ret;
	}();

	const SSUtils::uint32 VEDAFile::KeyLength = 128;
	const std::string VEDAFile::IndexTag("Index");
	const std::string VEDAFile::OriginNameAttr("OriginName");
	const std::string VEDAFile::PublicKeyTag("PublicKey");
	const std::string VEDAFile::PrivateKeyTag("PrivateKey");
	const std::string VEDAFile::SignationTokenTag("SignationToken");
	const std::string VEDAFile::VerificationTokenTag("VerificationToken");

	VEDAFile::VEDAFile(const std::string & url, const Type type)
		: m_name(SSUtils::File::getFileNameOfUrl(url)), m_path(SSUtils::File::getPathOfUrl(url)), m_type(type)
	{
		auto keyPair(SSUtils::Encryption::RSA::generateKey(KeyLength));
		m_verifier.publicKey.assign(keyPair.first);
		m_signer.privateKey.assign(keyPair.second);
		m_verificationToken = SSUtils::Data::generateRandomBlock(KeyLength);
	}

	const bool VEDAFile::isChildFile(const VEDAFile & file) const
	{
		return m_verifier(SSUtils::Data::toString(m_verificationToken) + file.m_originName, SSUtils::Data::toString(file.m_signationToken));
	}

	const bool VEDAFile::init(const std::shared_ptr<SSUtils::XML::Node> node)
	{
		if (node->getTag() != IndexTag
			|| node->countChild(PublicKeyTag) != 1
			|| node->countChild(PrivateKeyTag) != 1
			|| node->countChild(SignationTokenTag) != 1
			|| node->countChild(VerificationTokenTag) != 1)
		{
			return false;
		}

		const auto publicKeyNode(node->getChildren()[node->findChild(PublicKeyTag)]);
		const auto privateKeyNode(node->getChildren()[node->findChild(PrivateKeyTag)]);
		const auto signationTokenNode(node->getChildren()[node->findChild(SignationTokenTag)]);
		const auto verificationTokenNode(node->getChildren()[node->findChild(VerificationTokenTag)]);

		if (!signationTokenNode->hasAttr(OriginNameAttr))
		{
			return false;
		}

		m_verifier.publicKey.assign(SSUtils::String::base64Decode(publicKeyNode->getContent()));
		m_signer.privateKey.assign(SSUtils::String::base64Decode(privateKeyNode->getContent()));
		m_originName = signationTokenNode->getAttr(OriginNameAttr);
		m_signationToken = SSUtils::Data::fromBase64String(signationTokenNode->getContent());
		m_verificationToken = SSUtils::Data::fromBase64String(verificationTokenNode->getContent());

		return true;
	}

	const bool VEDAFile::init(const VEDAFile & parentFile, const std::string & name)
	{
		m_originName.assign(name);

		const auto &signer = parentFile.getSigner();
		m_signationToken = SSUtils::Data::fromString(signer(SSUtils::Data::toString(parentFile.getVerificationToken()) + name));

		return true;
	}

	std::shared_ptr<SSUtils::XML::Node> VEDAFile::normalizeIndexParameter(void) const
	{
		auto node(SSUtils::XML::Node::generate(IndexTag));

		auto publicKeyNode(SSUtils::XML::Node::generate(PublicKeyTag));
		auto privateKeyNode(SSUtils::XML::Node::generate(PrivateKeyTag));
		auto signationTokenNode(SSUtils::XML::Node::generate(SignationTokenTag));
		auto verificationTokenNode(SSUtils::XML::Node::generate(VerificationTokenTag));

		publicKeyNode->setContent(SSUtils::String::base64Encode(m_verifier.publicKey));
		privateKeyNode->setContent(SSUtils::String::base64Decode(m_signer.privateKey));
		signationTokenNode->setContent(SSUtils::Data::toBase64String(m_signationToken));
		signationTokenNode->setAttr(OriginNameAttr, m_originName);
		verificationTokenNode->setContent(SSUtils::Data::toBase64String(m_verificationToken));

		node->addChild(publicKeyNode);
		node->addChild(privateKeyNode);
		node->addChild(signationTokenNode);
		node->addChild(verificationTokenNode);

		return node;
	}
};
