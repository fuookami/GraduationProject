#include "VEDAInitOperationDialog.h"
#include "VEDAProjectFile.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include <QtWidgets/QFileDialog>
#include <thread>

namespace VEDA
{
	const std::string VEDAInitOperationDialog::DialogTitle("新建实验操作");

	VEDAInitOperationDialog * VEDAInitOperationDialog::getInstance(VEDAProcessFile *processFile)
	{
		return new VEDAInitOperationDialog(processFile);
	}

	VEDAInitOperationDialog::VEDAInitOperationDialog(VEDAProcessFile *processFile)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitOperationDialogUrl.c_str()), nullptr),
		m_processFile(processFile), m_interface(new VEDAInitOperationDialogInterface(this, processFile))
	{
	}

	void VEDAInitOperationDialog::registerContents(void)
	{
		registerObject(m_interface);
	}

	void VEDAInitOperationDialog::initGUI(void)
	{
		m_view->page()->runJavaScript(QString("setPath('%1')")
			.arg(QString::fromLocal8Bit(SSUtils::File::getLinuxUrl(m_processFile->getPath()).c_str())));
	}

	VEDAInitOperationDialogInterface::VEDAInitOperationDialogInterface(VEDAInitOperationDialog *dialog, VEDAProcessFile *processFile)
		: IWebEngineDialogInterface(dialog), m_processFile(processFile), m_methodModule(CARSDK::ExperimentalDesignMethodModule::instance())
	{

	}

	void VEDAInitOperationDialogInterface::emitInitOperationFailed(const QString & info)
	{
	}

	void VEDAInitOperationDialogInterface::emitInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>)
	{
	}

	void VEDAInitOperationDialogInterface::onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>)
	{
	}

	void VEDAInitOperationDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitOperationDialogInterface::onMethodRequested(void)
	{
		
	}

	void VEDAInitOperationDialogInterface::onCategoryRequested(QJsonValue method)
	{
		
	}

	void VEDAInitOperationDialogInterface::onAttributeRequested(QJsonValue method, QJsonValue category)
	{
		
	}

	void VEDAInitOperationDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue method, QJsonValue category, QJsonValue attributes)
	{
		
	}

	void VEDAInitOperationDialogInterface::onCancelBtnClicked(void)
	{
		
	}
};
