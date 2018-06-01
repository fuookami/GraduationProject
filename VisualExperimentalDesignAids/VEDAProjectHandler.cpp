#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "SSUtils\FileUtils.h"
#include "SSUtils\XMLUtils.h"
#include "SSUtils\ThreadUtils.h"

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
		connect(this, &VEDAProjectHandler::sig_emitLoadingBegin, this, &VEDAProjectHandler::onEmitLoadingBegin);
		connect(this, &VEDAProjectHandler::sig_emitLoadingEnd, this, &VEDAProjectHandler::onEmitLoadingEnd);
		connect(this, &VEDAProjectHandler::sig_emitOpenProjectFinished, this, &VEDAProjectHandler::onEmitOpenProjectFinished);
		connect(this, &VEDAProjectHandler::sig_emitCloseProjectFinished, this, &VEDAProjectHandler::onEmitCloseProjectFinished);
	}

	void VEDAProjectHandler::emitLoadingBegin(void)
	{
		emit sig_emitLoadingBegin();
	}

	void VEDAProjectHandler::emitLoadingEnd(void)
	{
		emit sig_emitLoadingEnd();
	}

	void VEDAProjectHandler::emitOpenProjectFinished(const bool ok, const QString & info)
	{
		emit sig_emitOpenProjectFinished(ok, info);
	}

	void VEDAProjectHandler::emitCloseProjectFinished(const bool ok, const QString & info)
	{
		emit sig_emitCloseProjectFinished(ok, info);
	}

	void VEDAProjectHandler::onEmitLoadingBegin(void)
	{
		emit loadingBegin();
	}

	void VEDAProjectHandler::onEmitLoadingEnd(void)
	{
		emit loadingEnd();
	}

	void VEDAProjectHandler::onEmitOpenProjectFinished(bool ok, QString info)
	{
		emit openProjectFinished(ok, info);
	}

	void VEDAProjectHandler::onEmitCloseProjectFinished(bool ok, QString info)
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
		auto project(VEDAProjectFile::generate(projectFileUrl));
		if (!project->save())
		{
			return std::make_pair(false, std::string("创建项目文件失败：") + projectFileUrl);
		}

		return std::make_pair(true, projectFileUrl);
	}

	const std::tuple<bool, std::string, std::shared_ptr<VEDAProcessFile>> VEDAProjectHandler::initProcess(VEDAProjectFile * projectFile, const std::string & name, const std::string & path, const bool newDir)
	{
		std::string basePath(newDir ? (path + SSUtils::File::PathSeperator() + name) : path);
		if (!SSUtils::File::insurePathExist(basePath))
		{
			return std::make_tuple(false, std::string("创建目录失败：") + basePath, std::shared_ptr<VEDAProcessFile>());
		}

		std::string processFileUrl(basePath + SSUtils::File::PathSeperator() + name + SSUtils::File::ExtensionSeperator() + ProcessFileExtension);
		auto process(VEDAProcessFile::generate(processFileUrl, *projectFile));
		if (!process->save())
		{
			return std::make_tuple(false, std::string("创建流程文件失败：") + processFileUrl, std::shared_ptr<VEDAProcessFile>());
		}

		return std::make_tuple(true, processFileUrl, process);
	}

	const std::tuple<bool, std::string, std::shared_ptr<VEDAModelFile>> VEDAProjectHandler::initModel(VEDAProcessFile * processFile, const std::string & name, const std::string & path)
	{
		if (!SSUtils::File::insurePathExist(path))
		{
			return std::make_tuple(false, std::string("创建目录失败：") + path, std::shared_ptr<VEDAModelFile>());
		}

		std::string modelFileUrl(path + SSUtils::File::PathSeperator() + name + SSUtils::File::ExtensionSeperator() + ModelFileExtension);
		auto model(VEDAModelFile::generate(modelFileUrl, *processFile, XSDFrontend::XSDModel::generateNewXSDModel()));
		if (!model->save())
		{
			return std::make_tuple(false, std::string("创建模型文件失败：") + modelFileUrl, std::shared_ptr<VEDAModelFile>());
		}

		return std::make_tuple(true, modelFileUrl, model);
	}

	void VEDAProjectHandler::openProject(const std::string & projectFileUrl, const bool save)
	{
		closeCurrProject(save);
		SSUtils::XML::Document doc(SSUtils::XML::Document::fromFile(projectFileUrl, SSUtils::CharType::UTF8));
		
		QString fileName(QString::fromLocal8Bit(SSUtils::File::getFileNameOfUrl(projectFileUrl).c_str()));
		if (doc.getRoots().size() != 1)
		{
			emitOpenProjectFinished(false, QString::fromLocal8Bit("%1 不是一个有效的实验项目文件").arg(fileName));
			return;
		}
		
		m_currProject = VEDAProjectFile::generate(projectFileUrl, doc.getRoots().front());
		if (m_currProject == nullptr)
		{
			emitOpenProjectFinished(false, QString::fromLocal8Bit("%1 不是一个有效的实验项目文件").arg(fileName));
			return;
		}

		emitOpenProjectFinished(true, QString::fromLocal8Bit(projectFileUrl.c_str()));
	}

	void VEDAProjectHandler::closeCurrProject(const bool save)
	{
		if (save)
		{
			saveCurrProject();
		}
	}

	void VEDAProjectHandler::saveCurrProject(void)
	{
		if (m_currProject != nullptr)
		{

		}
	}
};
