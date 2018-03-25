#include "VEDAAboutDialog.h"
#include "VEDAVersion.h"
#include "VEDAGlobal.h"
#include "VEDAGUIEnterence.h"
#include <QtGui/QDesktopServices>

namespace VEDA
{
	const std::string VEDAAboutDialog::DialogTitle("关于可视化实验设计辅助工具");

	VEDAAboutDialog *VEDAAboutDialog::getInstance(void)
	{
		return new VEDAAboutDialog();
	}

	VEDAAboutDialog::VEDAAboutDialog(void)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::AboutDialogUrl.c_str()), nullptr), 
		m_interface(new VEDAAboutDialogInterface(this))
	{
		setWindowTitle(QString::fromLocal8Bit(DialogTitle.c_str()));
		setMinimumSize(Width, Height);
		setMaximumSize(Width, Height);
		resize(Width, Height);
	}

	void VEDAAboutDialog::registerContents(void)
	{
		m_webWidget->registerObject(m_interface);
	}

	void VEDAAboutDialog::initGUI(void)
	{
		m_web->page()->runJavaScript(QString::fromLocal8Bit("setInfo('%1', '%2')").arg(QString::fromLocal8Bit(Version.c_str())).arg(QString::fromLocal8Bit(BuildDatetime.c_str())));
	}

	VEDAAboutDialogInterface::VEDAAboutDialogInterface(VEDAAboutDialog * dialog)
		: IWebEngineDialogInterface(dialog)
	{
	}

	void VEDAAboutDialogInterface::onConfirmBtnClicked(void)
	{
		m_dialog->close();
	}

	void VEDAAboutDialogInterface::onGithubBtnClicked(void)
	{
		QDesktopServices::openUrl(QUrl(GithubUrl.c_str()));
	}

	void VEDAAboutDialogInterface::onCodingBtnClicked(void)
	{
		QDesktopServices::openUrl(QUrl(CodingUrl.c_str()));
	}
};
