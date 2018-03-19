#include "VEDAMenuBarHelp.h"
#include "VEDAAboutDialog.h"

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
