#include "VEDAMainWindow.h"
#include "VEDAGlobal.h"
#include "VEDAGUIGlobal.h"
#include "VEDAMenuBar.h"
#include "VEDAMainWidget.h"
#include "VEDAProjectHandler.h"
#include "ui_VEDAMainWindow.h"
#include "SSUtils/GUI/QLoadingWidget.h"
#include "SSUtils/GUI/QMessageBoxUtils.h"
#include "CARSDK/ExperimentalDesignMethodModule.h"
#include <QtWidgets/QDesktopWidget>

namespace VEDA
{
	const int VEDAMainWindow::MinimumWidth = VEDAMainWidget::TreeViewWidth + VEDAMainWidget::Space + VEDAMainWidget::MainViewMinimumWidth + 20;
	const int VEDAMainWindow::MinimumHeight = VEDAMainWindow::MinimumWidth * 9 / 16;

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

		initLoadingWidget();
		initConnections();
		initOthers();
		registerMetaType();

		m_mainWidget->init();
	}

	void VEDAMainWindow::initLoadingWidget(void)
	{
		auto loadingWidget = SSUtils::GUI::QLoadingWidget::getInstance();
		loadingWidget->setParent(this);
		loadingWidget->setUrl(QString::fromLocal8Bit(GUIResource::LoadingUrl.c_str()));
		loadingWidget->show();
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

		// Project Handler:
		connect(m_projectHandler.get(), &VEDAProjectHandler::loadingBegin, VEDAMainWindow::onLoadingBegin);
		connect(m_projectHandler.get(), &VEDAProjectHandler::loadingEnd, VEDAMainWindow::onLoadingEnd);
		connect(m_projectHandler.get(), &VEDAProjectHandler::openProjectFinished, VEDAMainWindow::onOpenProjectFinished);

		// Main Widget
		connect(m_mainWidget, &VEDAMainWidget::loadingBegin, VEDAMainWindow::onLoadingBegin);
		connect(m_mainWidget, &VEDAMainWidget::loadingEnd, VEDAMainWindow::onLoadingEnd);
	}

	void VEDAMainWindow::initOthers(void)
	{
		CARSDK::ExperimentalDesignMethodModule::instance(PluginPath);
	}

	void VEDAMainWindow::registerMetaType(void)
	{
		qRegisterMetaType<std::shared_ptr<VEDAProcessFile>>("std::shared_ptr<VEDAProcessFile>");
		qRegisterMetaType<std::shared_ptr<VEDAModelFile>>("std::shared_ptr<VEDAModelFile>");
		qRegisterMetaType<std::shared_ptr<VEDAOperationFile>>("std::shared_ptr<VEDAOperationFile>");
		qRegisterMetaType<std::shared_ptr<VEDADataFile>>("std::shared_ptr<VEDADataFile>");
	}

	void VEDAMainWindow::resizeEvent(QResizeEvent * event)
	{
		SSUtils::GUI::QLoadingWidget::getInstance()->resize(this->size());
	}

	void VEDAMainWindow::onLoadingBegin(void)
	{
		SSUtils::GUI::QLoadingWidget::getInstance()->show();
	}

	void VEDAMainWindow::onLoadingEnd(void)
	{
		SSUtils::GUI::QLoadingWidget::getInstance()->hide();
	}

	void VEDAMainWindow::onOpenProjectFinished(bool ok, QString info)
	{
		if (!ok)
		{
			SSUtils::GUI::QMessageBoxUtils::information(QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开实验项目失败：%1").arg(info));
		}
	}
};
