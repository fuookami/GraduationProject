#include "VEDAInitProcessDialog.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>

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

	void VEDAInitProcessDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePath, bool newDir)
	{
	}

	void VEDAInitProcessDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePath, bool newDir, QJsonValue modelName)
	{
	}

	void VEDAInitProcessDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
