#pragma once

#include "XMLUtils.h"
#include "EncryptionUtils/RSA.h"

namespace VEDA
{
	class VEDAProcess;

	class VEDAProject
	{
	public:
		inline static std::shared_ptr<VEDAProject> generate(const std::string &name);
		inline static std::shared_ptr<VEDAProject> generate(std::string &&name);

	private:
		VEDAProject(const std::string &name);
		VEDAProject(std::string &&name);
		void init(void);
		
	public:
		VEDAProject(const VEDAProject &ano) = delete;
		VEDAProject(VEDAProject &&ano) = delete;
		~VEDAProject(void);

		inline void setName(const std::string &name);
		inline void setName(std::string &&name);
		inline const std::string &getName(void) const;

		inline SSUtils::Encryption::RSA::signer &signer(void);
		inline const SSUtils::Encryption::RSA::signer &signer(void) const;

		inline SSUtils::Encryption::RSA::verifier &verifier(void);
		inline const SSUtils::Encryption::RSA::verifier &verifier(void) const;

		inline void setVerificationDataPiece(const std::string &name);
		inline void setVerificationDataPiece(std::string &&name);
		inline const std::string &getVerificationDataPiece(void) const;

		inline std::map<std::string, VEDAProcess> &processes(void);
		inline const std::map<std::string, VEDAProcess> &processes(void) const;

		SSUtils::XML::Document toXML(void);
		static std::shared_ptr<VEDAProject> fromXML(const SSUtils::XML::Document &doc);

	private:
		std::string m_name;

		SSUtils::Encryption::RSA::signer m_signer;
		SSUtils::Encryption::RSA::verifier m_verifier;
		std::string m_verificationDataPiece;

		std::map<std::string, VEDAProcess> m_processes;
	};
};
