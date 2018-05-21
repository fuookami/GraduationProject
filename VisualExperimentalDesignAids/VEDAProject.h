#pragma once

#include "XMLUtils.h"
#include "EncryptionUtils/RSA.h"
#include "XSDModel.h"

namespace VEDA
{
	class VEDAProcess;

	class VEDAProject
	{
	public:
		static const SSUtils::uint32 KeyLength;

	public:
		static std::shared_ptr<VEDAProject> generate(const std::string &name);
		static std::shared_ptr<VEDAProject> generate(std::string &&name);

	private:
		VEDAProject(const std::string &name);
		VEDAProject(std::string &&name);
		void init(void);

	public:
		VEDAProject(const VEDAProject &ano) = delete;
		VEDAProject(VEDAProject &&ano) = delete;
		~VEDAProject(void) = default;

		inline void setName(const std::string &name) { m_name.assign(name); }
		inline void setName(std::string &&name) { m_name.assign(std::move(name)); }
		inline const std::string &getName(void) const { return m_name; }

		inline void setPath(const std::string &path) { m_path.assign(path); }
		inline void setPath(std::string &&path) { m_path.assign(path); }
		inline const std::string &getPath(void) const { return m_path; }

		inline void setDataModelFileName(const std::string &name) { m_dataModelFileName.assign(name); }
		inline void setDataModelFileName(std::string &&name) { m_dataModelFileName.assign(std::move(name)); }
		inline const std::string &getDataModelFileName(void) const { return m_dataModelFileName; }

		inline SSUtils::Encryption::RSA::signer &signer(void) { return m_signer; }
		inline const SSUtils::Encryption::RSA::signer &signer(void) const { return m_signer; }

		inline SSUtils::Encryption::RSA::verifier &verifier(void) { return m_verifier; }
		inline const SSUtils::Encryption::RSA::verifier &verifier(void) const { return m_verifier; }

		inline void setVerificationToken(const SSUtils::Block &token) { m_verificationToken = token; }
		inline void setVerificationToken(SSUtils::Block &&token) { m_verificationToken = token; }
		inline const SSUtils::Block &getVerificationDataPiece(void) const { return m_verificationToken; }

		inline std::map<std::string, VEDAProcess> &processes(void) { return m_processes; }
		inline const std::map<std::string, VEDAProcess> &processes(void) const { return m_processes; }

		SSUtils::XML::Document toXML(void);
		static std::shared_ptr<VEDAProject> fromXML(const SSUtils::XML::Document &doc);

	private:
		std::string m_name;
		std::string m_path;
		std::string m_publicDataModelFileName;

		SSUtils::Encryption::RSA::signer m_signer;
		SSUtils::Encryption::RSA::verifier m_verifier;
		SSUtils::Block m_verificationToken;
		std::shared_ptr<XSDFrontend::XSDModel> m_dataModel;

		std::map<std::string, VEDAProcess> m_processes;
	};
};
