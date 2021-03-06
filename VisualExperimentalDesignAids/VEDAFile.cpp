#include "VEDAFile.h"
#include "VEDAGlobal.h"
#include "SSUtils/FileUtils.h"
#include <QtCore/QDebug>
#include <QString>

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
		ret.insert(pair_type(PublicModelFileExtension, Type::PublicModel));
		ret.insert(pair_type(ModelFileExtension, Type::Model));
		ret.insert(pair_type(DataFileExtension, Type::Data));
		ret.insert(pair_type(ReportFileExtension, Type::Report));
		ret.insert(pair_type(ReportConfigurationFileExtension, Type::ReportConfiguration));
		ret.insert(pair_type(ReportDataFileExtension, Type::ReportData));
		return ret;
	}();

	const boost::bimap<VEDAFile::Type, std::string> VEDAFile::Type2Display = 
		[]()
	{
		typedef boost::bimap<VEDAFile::Type, std::string> result_type;
		typedef result_type::value_type pair_type;

		result_type ret;
		ret.insert(pair_type(Type::Project, std::string("实验项目")));
		ret.insert(pair_type(Type::Process, std::string("实验流程")));
		ret.insert(pair_type(Type::Operation, std::string("实验操作")));
		ret.insert(pair_type(Type::PublicModel, std::string("公共模型")));
		ret.insert(pair_type(Type::Model, std::string("实验因素模型")));
		ret.insert(pair_type(Type::Data, std::string("实验数据")));
		ret.insert(pair_type(Type::Report, std::string("实验报告")));
		ret.insert(pair_type(Type::ReportConfiguration, std::string("实验报告设计")));
		ret.insert(pair_type(Type::ReportData, std::string("实验报告数据")));
		return ret;
	}();

	const SSUtils::uint32 VEDAFile::KeyLength = 1024;
	const SSUtils::uint32 VEDAFile::TokenLength = 128;
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
		m_verifier.publicKey.assign(keyPair.second);
		m_signer.privateKey.assign(keyPair.first);
		m_verificationToken = SSUtils::Data::generateRandomBlock(TokenLength);
	}

	const bool VEDAFile::isChildFile(const VEDAFile & file) const
	{
		return m_verifier(SSUtils::Data::toString(m_verificationToken) + file.m_originName, SSUtils::Data::toString(file.m_signationToken));
	}

	const bool VEDAFile::save(void) const
	{
		if (!SSUtils::File::insurePathExist(m_path))
		{
			return false;
		}

		return toXML().toFile(getUrl(), SSUtils::CharType::UTF8);
	}

	void VEDAFile::resetParent(const VEDAFile & file)
	{
		init(file, m_originName);
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

		m_verifier.publicKey.assign(SSUtils::Data::toHexString(SSUtils::Data::fromBase64String(publicKeyNode->getContent())));
		m_signer.privateKey.assign(SSUtils::Data::toHexString(SSUtils::Data::fromBase64String(privateKeyNode->getContent())));
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

		publicKeyNode->setContent(SSUtils::Data::toBase64String(SSUtils::Data::fromHexString(m_verifier.publicKey)));
		privateKeyNode->setContent(SSUtils::Data::toBase64String(SSUtils::Data::fromHexString(m_signer.privateKey)));
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
