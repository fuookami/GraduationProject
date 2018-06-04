#include "VEDAInitModelDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include <QtWidgets/QFileDialog>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <thread>

namespace VEDA
{
	const std::string VEDAInitModelDialog::DialogTitle("新建实验因素数据模型");

	VEDAInitModelDialog * VEDAInitModelDialog::getInstance(VEDAProcessFile *processFile)
	{
		return new VEDAInitModelDialog(processFile);
	}

	VEDAInitModelDialog::VEDAInitModelDialog(VEDAProcessFile *processFile)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitModelDialogUrl.c_str()), nullptr), 
		m_processFile(processFile), m_interface(new VEDAInitModelDialogInterface(this, processFile))
	{
	}

	void VEDAInitModelDialog::registerContents(void)
	{
		registerObject(m_interface);
	}

	void VEDAInitModelDialog::initGUI(void)
	{
		m_view->page()->runJavaScript(QString("setPath('%1')")
			.arg(QString::fromLocal8Bit(SSUtils::File::getLinuxUrl(m_processFile->getPath()).c_str())));
	}

	VEDAInitModelDialogInterface::VEDAInitModelDialogInterface(VEDAInitModelDialog *dialog, VEDAProcessFile *processFile)
		: IWebEngineDialogInterface(dialog), m_processFile(processFile)
	{
		connect(this, &VEDAInitModelDialogInterface::initModelSucceeded, this, &VEDAInitModelDialogInterface::onInitModelSucceeded);
	}

	void VEDAInitModelDialogInterface::emitInitModelFailed(const QString &info)
	{
		emit initModelFailed(info);
	}

	void VEDAInitModelDialogInterface::emitInitModelSucceeded(std::shared_ptr<VEDAModelFile> modelFile)
	{
		emit initModelSucceeded(modelFile);
	}

	void VEDAInitModelDialogInterface::onInitModelSucceeded(std::shared_ptr<VEDAModelFile>)
	{
		m_dialog->close();
	}

	void VEDAInitModelDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitModelDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());

		std::thread([this, name, savePath]() 
		{
			auto modelRet(VEDAProjectHandler::initModel(this->m_processFile, name, this->m_processFile->getPath()));
			if (!std::get<0>(modelRet))
			{
				this->emitInitModelFailed(QString::fromLocal8Bit(std::get<1>(modelRet).c_str()));
			}

			auto modelFile(std::get<2>(modelRet));
			modelFile->setParent(this->m_processFile);

			this->m_processFile->setModelFileUrl(SSUtils::File::getRelativeUrlOfPath(this->m_processFile->getPath(), modelFile->getUrl()));
			this->m_processFile->setModelFile(modelFile);
			this->m_processFile->save();
			this->emitInitModelSucceeded(modelFile);
		}).detach();
	}

	void VEDAInitModelDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
