#include "VEDAMainWindow.h"
#include "VEDAGlobal.h"
#include "VEDAGUIEnterence.h"
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
		m_web->load(QString::fromLocal8Bit(GUIEntrance::MainViewUrl.c_str()));

		connect(m_web->view(), &QWebEngineView::loadFinished, this, &VEDAMainWindow::onLoadFinished);
	}

	void VEDAMainWindow::onLoadFinished(bool ok)
	{
		if (!ok)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"),
				QString::fromLocal8Bit("无法打开GUI入口：%1，请确认是否错误。").arg(QString::fromLocal8Bit(GUIEntrance::MainViewUrl.c_str())));
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
		connect(m_ui->InitProjectBtn, &QAction::triggered, MenuBar::onInitProjectBtnClicked);
		connect(m_ui->OpenProjectBtn, &QAction::triggered, MenuBar::onOpenProjectBtnClicked);
		connect(m_ui->InitProcessBtn, &QAction::triggered, MenuBar::onInitProcessBtnClicked);
		connect(m_ui->ImportProcessBtn, &QAction::triggered, MenuBar::onImportProcessBtnClicked);
		connect(m_ui->CloseBtn, &QAction::triggered, MenuBar::onCloseBtnClicked);
		connect(m_ui->CloseProjectBtn, &QAction::triggered, MenuBar::onCloseProjectBtnClicked);
		connect(m_ui->SaveBtn, &QAction::triggered, MenuBar::onSaveBtnClicked);
		connect(m_ui->SaveAllBtn, &QAction::triggered, MenuBar::onSaveAllBtnClicked);
		connect(m_ui->ExitBtn, &QAction::triggered, MenuBar::onExitBtnClicked);

		// menu bar: export
		connect(m_ui->ExportReportBtn, &QAction::triggered, MenuBar::onExportReportBtnClicked);

		// menu bar: help
		connect(m_ui->AboutQtBtn, &QAction::triggered, MenuBar::onAboutQtBtnClicked);
		connect(m_ui->AboutBoostBtn, &QAction::triggered, MenuBar::onAboutBoostBtnClicked);
		connect(m_ui->AboutMaterializeBtn, &QAction::triggered, MenuBar::onAboutMaterializeBtnClicked);
		connect(m_ui->AboutBtn, &QAction::triggered, MenuBar::onAboutBtnClicked);
	}
};
