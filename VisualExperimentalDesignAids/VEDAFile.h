#pragma once

#include "SSUtils\EncryptionUtils\RSA.h"
#include "SSUtils\XMLUtils.h"
#include "SSUtils\FileUtils.h"
#include <boost/bimap.hpp>
#include <set>

namespace VEDA
{
	class VEDAFile abstract
	{
	public:
		enum class Type
		{
			Project,
			Process,
			Operation,
			PublicModel,
			Model,
			Data,
			Report,
			ReportConfiguration,
			ReportData
		};
		static const boost::bimap<std::string, Type> Extension2Type;
		static const boost::bimap<Type, std::string> Type2Display;

		static const SSUtils::uint32 KeyLength;
		static const SSUtils::uint32 TokenLength;
		static const std::string IndexTag;
		static const std::string UUIDTag;
		static const std::string OriginNameAttr;
		static const std::string PublicKeyTag;
		static const std::string PrivateKeyTag;
		static const std::string SignationTokenTag;
		static const std::string VerificationTokenTag;

	protected:
		VEDAFile(const std::string &url, const Type type);

	public:
		VEDAFile(const VEDAFile &ano) = delete;
		VEDAFile(VEDAFile &&ano) = delete;
		VEDAFile &operator=(const VEDAFile &rhs) = delete;
		VEDAFile &operator=(VEDAFile &&rhs) = delete;
		virtual ~VEDAFile(void) = default;

		inline void setName(const std::string &name) { m_name.assign(name); }
		inline void setName(std::string &&name) { m_name.assign(std::move(name)); }
		inline const std::string &getName(void) const { return m_name; }

		inline void setPath(const std::string &path) { m_path.assign(path); }
		inline void setPath(std::string &&path) { m_path.assign(path); }
		inline const std::string &getPath(void) const { return m_path; }

		inline const std::string getMainName(void) const { return SSUtils::File::getFileMainNameOfUrl(m_name); }
		inline const std::string getUrl(void) const { return m_path + m_name; }

		inline const Type getType(void) const { return m_type; }

		inline const SSUtils::Encryption::RSA::signer &getSigner(void) const { return m_signer; }
		inline const SSUtils::Encryption::RSA::verifier &getVerifier(void) const { return m_verifier; }

		inline const std::string getOriginName(void) const { return m_originName; }
		inline const SSUtils::Block &getSignationToken(void) const { return m_signationToken; }
		inline const SSUtils::Block &getVerificationToken(void) const { return m_verificationToken; }

		const bool isChildFile(const VEDAFile &file) const;

		const bool save(void) const;
		virtual SSUtils::XML::Document toXML(void) const = 0;

		void resetParent(const VEDAFile &file);

	protected:
		const bool init(const std::shared_ptr<SSUtils::XML::Node> node);
		const bool init(const VEDAFile &parentFile, const std::string & name);
		std::shared_ptr<SSUtils::XML::Node> normalizeIndexParameter(void) const;

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

	template<typename T>
	class IVEDAFileParentInterface
	{
	protected:
		IVEDAFileParentInterface(void) : m_parent(nullptr) {};
	public:
		IVEDAFileParentInterface(const IVEDAFileParentInterface &ano) = delete;
		IVEDAFileParentInterface(IVEDAFileParentInterface &&ano) = delete;
		IVEDAFileParentInterface &operator=(const IVEDAFileParentInterface &rhs) = delete;
		IVEDAFileParentInterface &operator=(IVEDAFileParentInterface &&rhs) = delete;
		virtual ~IVEDAFileParentInterface(void) = default;

		inline void setParent(T *parent) { m_parent = parent; }
		inline T *getParent(void) { return m_parent; }
		inline const T *getParent(void) const { return m_parent; }

	protected:
		T *m_parent;
	};

	template<typename T>
	class IVEDAFileIndexInterface
	{
	protected:
		IVEDAFileIndexInterface(void) = default;
	public:
		IVEDAFileIndexInterface(const IVEDAFileIndexInterface &ano) = delete;
		IVEDAFileIndexInterface(IVEDAFileIndexInterface &&ano) = delete;
		IVEDAFileIndexInterface &operator=(const IVEDAFileIndexInterface &rhs) = delete;
		IVEDAFileIndexInterface &operator=(IVEDAFileIndexInterface &&rhs) = delete;
		virtual ~IVEDAFileIndexInterface(void) = default;

		const bool hasDataFile(const std::string name) 
		{
			return std::find_if(m_dataFiles.cbegin(), m_dataFiles.cend(), 
				[&name](const std::string &url)
			{
				return SSUtils::File::getFileMainNameOfUrl(url) == name;
			}) != m_dataFiles.cend();
		}

		void addDataFile(const std::string &url, const std::shared_ptr<T> file)
		{
			m_dataFiles.insert(url);
			m_loadedDataFiles.insert(std::make_pair(url, file));
		}

		inline std::set<std::string> &getDataFileUrls(void) { return m_dataFiles; }
		inline const std::set<std::string> &getDataFileUrls(void) const { return m_dataFiles; }

		inline std::map<std::string, std::shared_ptr<T>> &getLoadedDataFiles(void) { return m_loadedDataFiles; }
		inline const std::map<std::string, std::shared_ptr<T>> &getLoadedDataFiles(void) const { return m_loadedDataFiles; }

	protected:
		virtual const std::string &IndexFileTag(void) const = 0;
		const bool initIndex(const std::vector<std::shared_ptr<SSUtils::XML::Node>> nodes)
		{
			for (const auto node : nodes)
			{
				if (node->getTag() == IndexFileTag())
				{
					m_dataFiles.insert(node->getContent());
				}
			}

			return true;
		}

		std::vector<std::shared_ptr<SSUtils::XML::Node>> normalizeIndexFiles(void) const
		{
			std::vector<std::shared_ptr<SSUtils::XML::Node>> ret;
			for (const auto &url : m_dataFiles)
			{
				auto dataFileNode(SSUtils::XML::Node::generate(IndexFileTag()));
				dataFileNode->setContent(url);
				ret.push_back(dataFileNode);
			}

			return ret;
		}
		
	protected:
		std::set<std::string> m_dataFiles;
		std::map<std::string, std::shared_ptr<T>> m_loadedDataFiles;
	};

	class VEDADataFile;
	class VEDAModelFile;
	class VEDAOperationFile;
	class VEDAProcessFile;
	class VEDAProjectFile;
	class VEDAReportFile;
	class VEDAReportConfigurationFile;
	class VEDAReportDataFile;
};
