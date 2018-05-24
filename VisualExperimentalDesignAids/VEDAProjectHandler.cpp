#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "VEDAProject.h"
#include "SSUtils\FileUtils.h"
#include "SSUtils\XMLUtils.h"

namespace VEDA
{
	std::shared_ptr<VEDAProjectHandler> VEDAProjectHandler::getInstance(void)
	{
		static std::shared_ptr<VEDAProjectHandler> instance(new VEDAProjectHandler());
		return instance;
	}

	VEDAProjectHandler::VEDAProjectHandler(void)
		: m_currProject(nullptr)
	{
	}

	void VEDAProjectHandler::emitOpenProjectFinished(const bool ok, const QString & info)
	{
		emit openProjectFinished(ok, info);
	}

	void VEDAProjectHandler::emitCloseProjectFinished(const bool ok, const QString & info)
	{
		emit closeProjectFinished(ok, info);
	}

	const std::pair<bool, std::string> VEDAProjectHandler::initProject(const std::string & name, const std::string & path, const bool newDir)
	{
		std::string basePath(newDir ? (path + SSUtils::File::PathSeperator() + name) : path);
		if (!SSUtils::File::insurePathExist(basePath))
		{
			return std::make_pair(false, std::string("创建目录失败：") + basePath);
		}

		std::string projectFileUrl(basePath + SSUtils::File::PathSeperator() + name + SSUtils::File::ExtensionSeperator() + ProjectFileExtension);
		
		auto project(VEDAProject::generate(name));
		auto doc(project->toXML());
		if (!doc.toFile(projectFileUrl, SSUtils::CharType::UTF8))
		{
			return std::make_pair(false, std::string("创建项目文件失败：") + projectFileUrl);
		}

		return std::make_pair(true, projectFileUrl);
	}

	void VEDAProjectHandler::openProject(const std::string & projectFileUrl, const bool save)
	{

	}

	void VEDAProjectHandler::closeCurrProject(const bool save)
	{
	}
};
