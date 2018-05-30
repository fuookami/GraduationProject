#pragma once

#include "VEDAFile.h"
#include "VEDAPublicModelFile.h"
#include "VEDAProcessFile.h"

namespace VEDA
{
	class VEDAProjectFile : public VEDAFile, public IVEDAFileIndexInterface<VEDAProcessFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAProjectFile> generate(const std::string &url);
		static std::shared_ptr<VEDAProjectFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAProjectFile(const std::string &url);
	public:
		VEDAProjectFile(const VEDAProjectFile &ano) = delete;
		VEDAProjectFile(VEDAProjectFile &&ano) = delete;
		VEDAProjectFile &operator=(const VEDAProjectFile &rhs) = delete;
		VEDAProjectFile &operator=(VEDAProjectFile &&rhs) = delete;
		~VEDAProjectFile(void) = default;

		inline const std::string &getPublicModelFileUrl(void) const { return m_publicModelFileUrl; }
		inline void setPublicModelFileUrl(const std::string &url) { m_publicModelFileUrl.assign(url); }
		inline void setPublicModelFileUrl(std::string &&url) { m_publicModelFileUrl.assign(std::move(url)); }

		inline const std::shared_ptr<VEDAPublicModelFile> getPublicModelFile(void) const { return m_publicModelFile; }
		inline void setPublicModelFile(const std::shared_ptr<VEDAPublicModelFile> &file) { m_publicModelFile = file; }

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &IndexFileTag(void) const override;

	private:
		std::string m_publicModelFileUrl;
		std::shared_ptr<VEDAPublicModelFile> m_publicModelFile;
	};
};
