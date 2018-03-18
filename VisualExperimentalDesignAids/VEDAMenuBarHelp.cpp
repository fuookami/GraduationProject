#include "VEDAMenuBarHelp.h"
#include "VEDAAboutDialog.h"
#include <QtCore/QDebug>

namespace VEDA
{
	namespace MenuBar
	{
		void onAboutBtnClicked(void)
		{
			static auto aboutDialog(VEDAAboutDialog::getInstance());
			aboutDialog->exec();
		}
	};
};
