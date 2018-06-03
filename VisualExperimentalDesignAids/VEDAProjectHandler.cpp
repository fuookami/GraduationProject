#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "SSUtils\FileUtils.h"
#include "SSUtils\XMLUtils.h"
#include "SSUtils\ThreadUtils.h"
#include "CARSDK\ExperimentalDesignTable.h"

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

	const std::pair<bool, std::string> VEDAProjectHandler::initPublicModel(const std::string & name, const std::string & path, const bool newDir)
	{
		// to do
		return std::pair<bool, std::string>();
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

	const std::tuple<bool, std::string, std::shared_ptr<VEDAOperationFile>> VEDAProjectHandler::initOperation(VEDAProcessFile * processFile, const std::string & name, const std::string & path, const bool newDir, const std::string & methodName, const std::string & methodCategory, const std::map<std::string, std::string>& methodAttributes)
	{
		std::string basePath(newDir ? (path + SSUtils::File::PathSeperator() + name) : path);
		if (!SSUtils::File::insurePathExist(basePath))
		{
			return std::make_tuple(false, std::string("创建目录失败：") + basePath, std::shared_ptr<VEDAOperationFile>());
		}

		std::string operationFileUrl(basePath + SSUtils::File::PathSeperator() + name + SSUtils::File::ExtensionSeperator() + OperationFileExtension);
		auto operation(VEDAOperationFile::generate(operationFileUrl, *processFile, methodName, methodCategory, methodAttributes));
		if (!operation->save())
		{
			return std::make_tuple(false, std::string("创建操作文件失败：") + operationFileUrl, std::shared_ptr<VEDAOperationFile>());
		}
		return std::make_tuple(true, operationFileUrl, operation);
	}

	const std::tuple<bool, std::string, std::shared_ptr<VEDADataFile>> VEDAProjectHandler::initData(VEDAOperationFile * operationFile, const std::string & name, const std::string & path, const bool newDir)
	{
		if (!SSUtils::File::insurePathExist(path))
		{
			return std::make_tuple(false, std::string("创建目录失败：") + path, std::shared_ptr<VEDADataFile>());
		}

		std::string dataFileUrl(path + SSUtils::File::PathSeperator() + name + SSUtils::File::ExtensionSeperator() + DataFileExtension);
		auto data(VEDADataFile::generate(dataFileUrl, *operationFile, XSDFrontend::XSDModel::generateNewXSDModel(), SSUtils::XML::Node::generate(CARSDK::ExperimentalDesignTable::Tag)));
		if (!data->save())
		{
			return std::make_tuple(false, std::string("创建模型文件失败：") + dataFileUrl, std::shared_ptr<VEDADataFile>());
		}

		return std::make_tuple(true, dataFileUrl, data);
	}

	void VEDAProjectHandler::openProject(const std::string & projectFileUrl, const bool save)
	{
		closeCurrProject(save);
		SSUtils::XML::Document projectDoc(SSUtils::XML::Document::fromFile(projectFileUrl, SSUtils::CharType::UTF8));
		
		QString fileName(QString::fromLocal8Bit(SSUtils::File::getFileNameOfUrl(projectFileUrl).c_str()));
		if (projectDoc.getRoots().size() != 1)
		{
			emitOpenProjectFinished(false, QString::fromLocal8Bit("%1 不是一个有效的实验项目文件").arg(fileName));
			return;
		}
		
		m_currProject = VEDAProjectFile::generate(projectFileUrl, projectDoc.getRoots().front());
		if (m_currProject == nullptr)
		{
			emitOpenProjectFinished(false, QString::fromLocal8Bit("%1 不是一个有效的实验项目文件").arg(fileName));
			return;
		}

		std::vector<std::string> invalidProcessUrl;
		for (const auto &url : m_currProject->getDataFileUrls())
		{
			std::string processFileUrl(SSUtils::File::getSystemNativePath(m_currProject->getPath() + url));
			auto process(openProcess(m_currProject.get(), processFileUrl));
			if (process == nullptr)
			{
				invalidProcessUrl.push_back(url);
				continue;
			}

			m_currProject->addDataFile(processFileUrl, process);
		}
		for (const auto &url : invalidProcessUrl)
		{
			m_currProject->getDataFileUrls().erase(url);
		}
		m_currProject->save();

		emitOpenProjectFinished(true, QString::fromLocal8Bit(projectFileUrl.c_str()));
	}

	std::shared_ptr<VEDAProcessFile> VEDAProjectHandler::openProcess(VEDAProjectFile *projectFile, const std::string & processFileUrl, const bool ignoreIsChild)
	{
		SSUtils::XML::Document processDoc(SSUtils::XML::Document::fromFile(processFileUrl, SSUtils::CharType::UTF8));
		if (processDoc.getRoots().size() != 1)
		{
			return nullptr;
		}

		auto process = VEDAProcessFile::generate(processFileUrl, processDoc.getRoots().front());
		if (!ignoreIsChild && projectFile->isChildFile(*process))
		{
			return nullptr;
		}

		std::vector<std::string> invalidOperationUrl;
		for (const auto &url : process->getDataFileUrls())
		{
			std::string operationFileUrl(SSUtils::File::getSystemNativePath(process->getPath() + url));
			auto operation(openOperation(process.get(), operationFileUrl));
			if (operation == nullptr)
			{
				invalidOperationUrl.push_back(url);
				continue;
			}

			process->addDataFile(operationFileUrl, operation);
		}
		for (const auto &url : invalidOperationUrl)
		{
			process->getDataFileUrls().erase(url);
		}
		process->save();

		return process;
	}

	std::shared_ptr<VEDAModelFile> VEDAProjectHandler::openModel(VEDAProcessFile * processFile, const bool ignoreIsChild)
	{
		SSUtils::XML::Document modelDoc(SSUtils::XML::Document::fromFile(processFile->getModelFileUrl(), SSUtils::CharType::UTF8));
		if (modelDoc.getRoots().size() != 1)
		{
			return nullptr;
		}

		auto model = VEDAModelFile::generate(processFile->getModelFileUrl(), modelDoc.getRoots().front());
		if (!ignoreIsChild && processFile->isChildFile(*model))
		{
			return nullptr;
		}

		return model;
	}

	std::shared_ptr<VEDAOperationFile> VEDAProjectHandler::openOperation(VEDAProcessFile * processFile, const std::string & operationFileUrl, const bool ignoreIsChild)
	{
		SSUtils::XML::Document operationDoc(SSUtils::XML::Document::fromFile(operationFileUrl, SSUtils::CharType::UTF8));
		if (operationDoc.getRoots().size() != 1)
		{
			return nullptr;
		}

		auto operation = VEDAOperationFile::generate(operationFileUrl, operationDoc.getRoots().front());
		if (!ignoreIsChild && processFile->isChildFile(*operation))
		{
			return nullptr;
		}
		return operation;
	}

	std::shared_ptr<VEDADataFile> VEDAProjectHandler::openData(VEDAOperationFile * operationFile, const std::string &dataFileUrl, const bool ignoreIsChild)
	{
		SSUtils::XML::Document dataDoc(SSUtils::XML::Document::fromFile(dataFileUrl, SSUtils::CharType::UTF8));
		if (dataDoc.getRoots().size() != 1)
		{
			return nullptr;
		}

		auto data = VEDADataFile::generate(dataFileUrl, dataDoc.getRoots().front());
		if (!ignoreIsChild && operationFile->isChildFile(*data))
		{
			return nullptr;
		}
		return data;
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
