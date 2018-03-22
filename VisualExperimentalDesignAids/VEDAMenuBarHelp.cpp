#include "VEDAMenuBarHelp.h"
#include "VEDAAboutDialog.h"
#include "QMessageBoxUtils.h"
#include <boost/version.hpp>

namespace VEDA
{
	namespace MenuBar
	{
		void onAboutQtBtnClicked(void)
		{
			QMessageBoxUtils::aboutQt();
		}

		void onAboutBoostBtnClicked(void)
		{
			static const QString Ttile(QString::fromLocal8Bit("����Boost"));
			static const QString Text(QString::fromLocal8Bit("�汾��%1").arg(BOOST_LIB_VERSION));
			QMessageBoxUtils::about(Ttile, Text);
		}

		void onAboutMaterializeBtnClicked(void)
		{
		}

		void onAboutBtnClicked(void)
		{
			static auto aboutDialog(VEDAAboutDialog::getInstance());
			aboutDialog->exec();
		}
	};
};
