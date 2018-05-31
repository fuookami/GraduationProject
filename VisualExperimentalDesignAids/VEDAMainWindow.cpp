#include "VEDAMainWindow.h"
#include "VEDAGlobal.h"
#include "VEDAGUIEnterence.h"
#include "VEDAMenuBar.h"
#include "VEDAMainWidget.h"
#include "VEDAProjectHandler.h"
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
		: QMainWindow(nullptr), m_ui(new Ui::VEDAMainWindow()), m_projectHandler(VEDAProjectHandler::getInstance()), m_mainWidget(new VEDAMainWidget())
	{
		m_ui->setupUi(this);
		this->setCentralWidget(m_mainWidget);

		setMinimumSize(QSize(MinimumWidth, MinimumHeight));

		initConnections();
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
