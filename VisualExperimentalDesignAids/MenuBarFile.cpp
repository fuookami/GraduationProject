#include "VEDAMenuBarFile.h"
#include "VEDAMainWindow.h"

namespace VEDA
{
	namespace MenuBar
	{
		void onExitBtnClicked(void)
		{
			VEDAMainWindow::getInstance()->close();
		}
	};
};
