#include "VEDAMainWindow.h"
#include "VEDAGlobal.h"
#include "VEDAMenuBar.h"
#include "ui_VEDAMainWindow.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDesktopWidget>

namespace VEDA
{
	std::shared_ptr<VEDAMainWindow> VEDAMainWindow::getInstance(void)
	{
		static std::shared_ptr<VEDAMainWindow> instance(new VEDAMainWindow());
		return instance;
	}

	VEDAMainWindow::VEDAMainWindow(void)
		: QMainWindow(nullptr), m_ui(new Ui::VEDAMainWindow), m_web(new QWebEngineWidget(nullptr))
	{
		m_ui->setupUi(this);
		this->setCentralWidget(m_web);

		setMinimumSize(QSize(MinimumWidth, MinimumHeight));

		registerContents();
		m_web->load(QString::fromLocal8Bit(GUIEntrance.c_str()));

		connect(m_web->view(), &QWebEngineView::loadFinished, this, &VEDAMainWindow::onLoadFinished);
	}

	void VEDAMainWindow::onLoadFinished(bool ok)
	{
		if (!ok)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"),
				QString::fromLocal8Bit("无法打开GUI入口：%1，请确认是否错误。").arg(QString::fromLocal8Bit(GUIEntrance.c_str())));
			this->close();
		}
		else
		{
			initConnections();
		}
	}

	void VEDAMainWindow::registerContents(void)
	{
	}

	void VEDAMainWindow::initConnections(void)
	{
		// menu bar: file
		connect(m_ui->ExitBtn, &QAction::triggered, MenuBar::onExitBtnClicked);

		// menu bar: help
		connect(m_ui->AboutBtn, &QAction::triggered, MenuBar::onAboutBtnClicked);
	}
};
