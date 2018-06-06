#include "VEDAGlobal.h"
#include "VEDAMenuBarFile.h"
#include "VEDAInitProjectDialog.h"
#include "VEDAProjectHandler.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>
#include <thread>

namespace VEDA
{
	namespace MenuBar
	{
		void onInitProjectBtnClicked(void)
		{
			auto dialog(VEDAInitProjectDialog::getInstance());
			dialog->show();
		}

		void onOpenProjectBtnClicked(void)
		{
			auto projectHandler(VEDAProjectHandler::getInstance());
			QString _url = QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("选择要打开的项目文件"), QString(""), QString("*.%1").arg(QString(ProjectFileExtension.c_str())));
			if (!_url.isEmpty())
			{
				std::string url(_url.toLocal8Bit());

				std::thread([projectHandler, url]()
				{
					projectHandler->emitLoadingBegin();
					projectHandler->openProject(url);
					projectHandler->emitLoadingEnd();
				}).detach();
			}
		}

		void onInitProcessBtnClicked(void)
		{
			qDebug() << "to do: on init process btn clicked.";
		}

		void onImportProcessBtnClicked(void)
		{
			qDebug() << "to do: on import process btn clicked.";
		}

		void onCloseBtnClicked(void)
		{
			auto projectHandler(VEDAProjectHandler::getInstance());

			std::thread([projectHandler]()
			{
				projectHandler->emitLoadingBegin();
				projectHandler->closeCurrProject();
				projectHandler->emitCloseProjectFinished(true, QString(""));
				projectHandler->emitLoadingEnd();
			}).detach();
		}

		void onCloseProjectBtnClicked(void)
		{
			qDebug() << "to do: on close project btn clicked.";
		}

		void onSaveBtnClicked(void)
		{
			qDebug() << "to do: on save btn clicked.";
		}

		void onSaveAllBtnClicked(void)
		{
			qDebug() << "to do: on save all btn clicked.";
		}

		void onExitBtnClicked(void)
		{
			QApplication::exit(0);
		}
	};
};
