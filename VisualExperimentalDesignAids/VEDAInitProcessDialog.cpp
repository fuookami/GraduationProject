#include "VEDAInitProcessDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include <QtWidgets/QFileDialog>
#include <thread>

namespace VEDA
{
	const std::string VEDAInitProcessDialog::DialogTitle("新建实验流程");

	VEDAInitProcessDialog * VEDAInitProcessDialog::getInstance(VEDAProjectFile *projectFile)
	{
		return new VEDAInitProcessDialog(projectFile);
	}

	VEDAInitProcessDialog::VEDAInitProcessDialog(VEDAProjectFile *projectFile)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitProcessDialogUrl.c_str()), nullptr), 
		m_projectFile(projectFile), m_interface(new VEDAInitProcessDialogInterface(this, projectFile))
	{
	}

	void VEDAInitProcessDialog::registerContents(void)
	{
		registerObject(m_interface);
	}

	void VEDAInitProcessDialog::initGUI(void)
	{
		m_view->page()->runJavaScript(QString("setPath('%1')")
			.arg(QString::fromLocal8Bit(SSUtils::File::getLinuxUrl(m_projectFile->getPath()).c_str())));
	}

	VEDAInitProcessDialogInterface::VEDAInitProcessDialogInterface(VEDAInitProcessDialog *dialog, VEDAProjectFile *projectFile)
		: IWebEngineDialogInterface(dialog), m_projectFile(projectFile)
	{
		connect(this, &VEDAInitProcessDialogInterface::initProcessSucceeded, this, &VEDAInitProcessDialogInterface::onInitProcessSucceeded);
	}

	void VEDAInitProcessDialogInterface::emitInitProcessFailed(const QString &info)
	{
		emit initProcessFailed(info);
	}

	void VEDAInitProcessDialogInterface::emitInitProcessSucceeded(std::shared_ptr<VEDAProcessFile> processFile)
	{
		emit initProcessSucceeded(processFile);
	}

	void VEDAInitProcessDialogInterface::onInitProcessSucceeded(std::shared_ptr<VEDAProcessFile> processFile)
	{
		m_dialog->close();
	}

	void VEDAInitProcessDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitProcessDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());

		if (name.empty() || savePath.empty())
		{
			this->emitInitProcessFailed(QString::fromLocal8Bit("实验流程名称和实验流程保存位置均不能为空。"));
		}
		else if (m_projectFile->hasDataFile(name))
		{
			this->emitInitProcessFailed(QString::fromLocal8Bit("实验项目%1下已有实验流程%2").arg(QString::fromLocal8Bit(m_projectFile->getMainName().c_str()).arg(QString::fromLocal8Bit(name.c_str()))));
		}
		else
		{
			std::thread([this, name, savePath, newDir]
			{
				auto ret(VEDAProjectHandler::initProcess(this->m_projectFile, name, savePath, newDir));
				if (!std::get<0>(ret))
				{
					this->emitInitProcessFailed(QString::fromLocal8Bit(std::get<1>(ret).c_str()));
				}
				else
				{
					auto processFile(std::get<2>(ret));
					this->m_projectFile->addDataFile(SSUtils::File::getRelativeUrlOfPath(this->m_projectFile->getPath(), processFile->getUrl()), processFile);
					this->m_projectFile->save();
					this->emitInitProcessSucceeded(processFile);
				}
			}).detach();
		}
	}

	void VEDAInitProcessDialogInterface::onConfirmBtnClickedWithModel(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue modelNameValue)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());
		std::string modelName(modelNameValue.toString().toLocal8Bit());

		if (name.empty() || savePath.empty() || modelName.empty())
		{
			this->emitInitProcessFailed(QString::fromLocal8Bit("实验流程名称、实验流程保存位置和实验因素数据模型名称均不能为空。"));
		}
		else if (m_projectFile->hasDataFile(name))
		{
			this->emitInitProcessFailed(QString::fromLocal8Bit("实验项目%1下已有实验流程%2").arg(QString::fromLocal8Bit(m_projectFile->getMainName().c_str()).arg(QString::fromLocal8Bit(name.c_str()))));
		}
		else
		{
			std::thread([this, name, savePath, modelName, newDir]
			{
				auto processRet(VEDAProjectHandler::initProcess(this->m_projectFile, name, savePath, newDir));
				if (!std::get<0>(processRet))
				{
					this->emitInitProcessFailed(QString::fromLocal8Bit(std::get<1>(processRet).c_str()));
				}
				else
				{
					auto processFile(std::get<2>(processRet));

					auto modelRet(VEDAProjectHandler::initModel(processFile.get(), modelName, processFile->getPath()));
					if (!std::get<0>(modelRet))
					{
						SSUtils::File::removeFile(processFile->getUrl());
						this->emitInitProcessFailed(QString::fromLocal8Bit(std::get<1>(modelRet).c_str()));
					}
					else
					{
						auto modelFile(std::get<2>(modelRet));

						processFile->setModelFileUrl(SSUtils::File::getRelativeUrlOfPath(processFile->getPath(), modelFile->getUrl()));
						processFile->setModelFile(modelFile);
						processFile->save();

						this->m_projectFile->addDataFile(SSUtils::File::getRelativeUrlOfPath(this->m_projectFile->getPath(), processFile->getUrl()), processFile);
						this->m_projectFile->save();
						this->emitInitProcessSucceeded(processFile);
					}
				}
			}).detach();
		}
	}

	void VEDAInitProcessDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
