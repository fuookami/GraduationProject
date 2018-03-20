#include "VEDAMenuBarFile.h"
#include "VEDAInitProjectDialog.h"
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>

namespace VEDA
{
	namespace MenuBar
	{
		void onInitProjectBtnClicked(void)
		{
			auto dialog(VEDAInitProjectDialog::getInstance());
			dialog->exec();
		}

		void onOpenProjectBtnClicked(void)
		{
			qDebug() << "to do: on open protject btn clicked.";
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
			qDebug() << "to do: on close btn clicked.";
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
