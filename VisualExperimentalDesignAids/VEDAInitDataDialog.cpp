#include "VEDAInitDataDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include "CARSDK\ExperimentalDesignMethodModule.h"
#include <QtWidgets\QFileDialog>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <thread>

namespace VEDA
{
	const std::string VEDAInitDataDialog::DialogTitle("新建实验数据");

	VEDAInitDataDialog * VEDAInitDataDialog::getInstance(VEDAOperationFile *operationFile)
	{
		return new VEDAInitDataDialog(operationFile);
	}

	VEDAInitDataDialog::VEDAInitDataDialog(VEDAOperationFile *operationFile)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitDataDialogUrl.c_str()), nullptr),
		m_operationFile(operationFile), m_interface(new VEDAInitDataDialogInterface(this, operationFile))
	{
	}

	void VEDAInitDataDialog::registerContents(void)
	{
		registerObject(m_interface);
	}

	void VEDAInitDataDialog::initGUI(void)
	{
		m_view->page()->runJavaScript(QString("setPath('%1')")
			.arg(QString::fromLocal8Bit(SSUtils::File::getLinuxUrl(m_operationFile->getPath()).c_str())));
	}

	VEDAInitDataDialogInterface::VEDAInitDataDialogInterface(VEDAInitDataDialog *dialog, VEDAOperationFile *operationFile)
		: IWebEngineDialogInterface(dialog), m_operationFile(operationFile)
	{
		connect(this, &VEDAInitDataDialogInterface::initDataSucceeded, this, &VEDAInitDataDialogInterface::onInitDataSucceeded);
	}

	void VEDAInitDataDialogInterface::emitInitDataFailed(const QString & info)
	{
		emit initDataFailed(info);
	}

	void VEDAInitDataDialogInterface::emitInitDataSucceeded(std::shared_ptr<VEDADataFile> dataFile)
	{
		emit initDataSucceeded(dataFile);
	}

	void VEDAInitDataDialogInterface::onInitDataSucceeded(std::shared_ptr<VEDADataFile>)
	{
		m_dialog->close();
	}

	void VEDAInitDataDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitDataDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());

		std::thread([this, name, savePath]()
		{
			auto *operation(this->m_operationFile);
			auto *process(operation->getParent());
			if (process->getModelFileUrl().empty())
			{
				this->emitInitDataFailed(QString::fromLocal8Bit("该实验流程下没有实验因素数据模型，请先创建实验因素数据模型"));
				return;
			}
			if (process->getModelFile() == nullptr && VEDAProjectHandler::openModel(process) == nullptr)
			{
				this->emitInitDataFailed(QString::fromLocal8Bit("打开该实验流程下的实验因素数据模型时出错"));
				return;
			}
			auto model(process->getModelFile()->getModel());

			auto methodModule(CARSDK::ExperimentalDesignMethodModule::instance(PluginPath));
			auto methodUtil(methodModule->util(this->m_operationFile->getDesignMethodName()));
			if (methodUtil == nullptr)
			{
				this->emitInitDataFailed(QString::fromLocal8Bit("找不到实验设计方法工具集：%1").arg(QString::fromLocal8Bit(this->m_operationFile->getDesignMethodName().c_str())));
				return;
			}
			auto methodInterface(methodUtil->method(this->m_operationFile->getDesignMethodCategory()));
			if (methodInterface == nullptr)
			{
				this->emitInitDataFailed(QString::fromLocal8Bit("在%1中找不到实验设计方法类别：%2").arg(QString::fromLocal8Bit(methodUtil->displayName().c_str())).arg(QString::fromLocal8Bit(this->m_operationFile->getDesignMethodCategory().c_str())));
				return;
			}

			auto data = methodInterface->generateExperimentalDesignTable(model, operation->getAttributes());
			if (data.empty())
			{
				this->emitInitDataFailed(QString::fromLocal8Bit(methodInterface->lastError().c_str()));
				return;
			}

			auto dataRet(VEDAProjectHandler::initData(operation, name, savePath, model, data));
			if (!std::get<0>(dataRet))
			{
				this->emitInitDataFailed(QString::fromLocal8Bit(std::get<1>(dataRet).c_str()));
				return;
			}

			auto dataFile(std::get<2>(dataRet));
			dataFile->setParent(operation);

			operation->addDataFile(SSUtils::File::getRelativeUrlOfPath(operation->getPath(), dataFile->getUrl()), dataFile);
			operation->save();
			this->emitInitDataSucceeded(dataFile);
		}).detach();
	}

	void VEDAInitDataDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
