#pragma once

#include "VEDAFile.h"
#include "VEDADataFile.h"

namespace VEDA
{
	class VEDAOperationFile : public VEDAFile, public IVEDAFileParentInterface<VEDAProcessFile>, public IVEDAFileIndexInterface<VEDADataFile>
	{
	public:
		static const std::string Tag;
		static const std::string MethodTag;
		static const std::string MethodNameTag;
		static const std::string MethodCategoryTag;
		static const std::string MethodAttributeTag;

	public:
		static std::shared_ptr<VEDAOperationFile> generate(const std::string &url, const VEDAFile &parentFile, const std::string &designMethodName, const std::string &designMethodCategory, const std::map<std::string, std::string> &attrs);
		static std::shared_ptr<VEDAOperationFile> generate(const std::string &url, const std::shared_ptr<SSUtils::XML::Node> node);

	private:
		VEDAOperationFile(const std::string &url);
	public:
		VEDAOperationFile(const VEDAOperationFile &ano) = delete;
		VEDAOperationFile(VEDAOperationFile &&ano) = delete;
		VEDAOperationFile &operator=(const VEDAOperationFile &rhs) = delete;
		VEDAOperationFile &operator=(VEDAOperationFile &&rhs) = delete;
		~VEDAOperationFile(void) = default;

		inline const std::string &getDesignMethodName(void) const { return m_designMethodName; }
		inline const std::string &getDesignMethodCategory(void) const { return m_designMethodCategory; }
		inline const std::map<std::string, std::string> &getAttributes(void) const { return m_attrs; }

		SSUtils::XML::Document toXML(void) const override;

	protected:
		const std::string &IndexFileTag(void) const override;

	private:
		std::shared_ptr<SSUtils::XML::Node> normalizeExperimentalDesignMethodParameter(void) const;

	private:
		std::string m_designMethodName;
		std::string m_designMethodCategory;
		std::map<std::string, std::string> m_attrs;
	};
};
