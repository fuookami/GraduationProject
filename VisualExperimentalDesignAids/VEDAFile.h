#pragma once

#include "SSUtils\EncryptionUtils\RSA.h"
#include "SSUtils\XMLUtils.h"
#include <boost/bimap.hpp>

namespace VEDA
{
	class VedaFile abstract
	{
	public:
		enum class Type
		{
			Project,
			Process,
			Operation,
			Model,
			Data,
			Report,
			ReportConfiguration,
			ReportData
		};
		static const boost::bimap<std::string, Type> Extension2Type;

		static const SSUtils::uint32 KeyLength;
		static const std::string IndexTag;
		static const std::string OriginNameAttr;
		static const std::string PublicKeyTag;
		static const std::string PrivateKeyTag;
		static const std::string SignationTokenTag;
		static const std::string VerificationTokenTag;

	protected:
		VedaFile(const std::string &url, const Type type);

	public:
		VedaFile(const VedaFile &ano) = default;
		VedaFile(VedaFile &&ano) = default;
		VedaFile &operator=(const VedaFile &rhs) = default;
		VedaFile &operator=(VedaFile &&rhs) = default;
		~VedaFile(void) = default;

		inline void setName(const std::string &name) { m_name.assign(name); }
		inline void setName(std::string &&name) { m_name.assign(std::move(name)); }
		inline const std::string &getName(void) const { return m_name; }

		inline void setPath(const std::string &path) { m_path.assign(path); }
		inline void setPath(std::string &&path) { m_path.assign(path); }
		inline const std::string &getPath(void) const { return m_path; }

		inline const Type getType(void) const { return m_type; }

		inline const SSUtils::Encryption::RSA::signer &getSigner(void) const { return m_signer; }
		inline const SSUtils::Encryption::RSA::verifier &getVerifier(void) const { return m_verifier; }

		inline const std::string getOriginName(void) const { return m_originName; }
		inline const SSUtils::Block &getSignationToken(void) const { return m_signationToken; }
		inline const SSUtils::Block &getVerificationToken(void) const { return m_verificationToken; }

		const bool isChildFile(const VedaFile &file) const;

		virtual SSUtils::XML::Document toXML(void) const = 0;

	protected:
		const bool init(const std::shared_ptr<SSUtils::XML::Node> node);
		const bool init(const VedaFile &parentFile, const std::string & name);
		std::shared_ptr<SSUtils::XML::Node> normalize(void) const;

	private:
		std::string m_name;
		std::string m_path;
		const Type m_type;

		SSUtils::Encryption::RSA::signer m_signer;
		SSUtils::Encryption::RSA::verifier m_verifier;

		std::string m_originName;
		SSUtils::Block m_signationToken;
		SSUtils::Block m_verificationToken;
	};
};
