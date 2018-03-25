#include "VEDAGUIEnterence.h"

namespace VEDA
{
	namespace GUIEntrance
	{
		const std::string WebRootPath("file:///WebRoot/");

		const std::string MainViewUrl = WebRootPath + std::string("main.html");

		const std::string DialogRootPath = WebRootPath + std::string("dialogs/");

		const std::string InitProjectDialogUrl = DialogRootPath + std::string("InitPorjectDialog.html");
		const std::string AboutDialogUrl = DialogRootPath + std::string("AboutDialog.html");
	};
}
