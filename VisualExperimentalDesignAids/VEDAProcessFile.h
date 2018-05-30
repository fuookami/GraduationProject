#pragma once

#include "VEDAFile.h"
#include "VEDAModelFile.h"
#include "VEDAOperationFile.h"

namespace VEDA
{
	class VEDAProcessFile : public VEDAFile, public IVEDAFileParentInterface<VEDAProjectFile>, public IVEDAFileIndexInterface<VEDAOperationFile>
	{
	public:
		static const std::string Tag;

	public:
		static std::shared_ptr<VEDAProcessFile> generate(const std::string &url, const VEDAFile &parentFile);
		static std::shared_ptr<VEDAProcessFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAProcessFile(const std::string &url);
	public:
		VEDAProcessFile(const VEDAProcessFile &ano) = delete;
		VEDAProcessFile(VEDAProcessFile &&ano) = delete;
		VEDAProcessFile &operator=(const VEDAProcessFile &rhs) = delete;
		VEDAProcessFile &operator=(VEDAProcessFile &&rhs) = delete;
		~VEDAProcessFile(void) = default;

		inline const std::string &getModelFileUrl(void) const { return m_modelFileUrl; }
		inline void setModelFileUrl(const std::string &url) { m_modelFileUrl.assign(url); }
		inline void setModelFileUrl(std::string &&url) { m_modelFileUrl.assign(std::move(url)); }

		inline const std::shared_ptr<VEDAModelFile> getModelFile(void) const { return m_modelFile; }
		inline void setModelFile(const std::shared_ptr<VEDAModelFile> &file) { m_modelFile = file; }

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &IndexFileTag(void) const override;

	private:
		std::string m_modelFileUrl;
		std::shared_ptr<VEDAModelFile> m_modelFile;
	};
};
