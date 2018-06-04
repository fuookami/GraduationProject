#include "VEDAGUIGlobal.h"
#include "SSUtils/FileUtils.h"

namespace VEDA
{
	namespace GUIEntrance
	{
		const std::string WebRootPath = std::string("file:///WebRoot/");

		const std::string ViewRootPath = WebRootPath + std::string("views/");

		const std::string HomeViewUrl = ViewRootPath + std::string("HomeView.html");
		const std::string ModelViewUrl = ViewRootPath + std::string("ModelView.html");
		const std::string DataViewUrl = ViewRootPath + std::string("DataView.html");
		const std::string AnalysisViewUrl = ViewRootPath + std::string("AnalysisView.html");

		const std::string DialogRootPath = WebRootPath + std::string("dialogs/");

		const std::string InitProjectDialogUrl = DialogRootPath + std::string("InitProjectDialog.html");
		const std::string InitProcessDialogUrl = DialogRootPath + std::string("InitProcessDialog.html");
		const std::string InitModelDialogUrl = DialogRootPath + std::string("InitModelDialog.html");
		const std::string InitOperationDialogUrl = DialogRootPath + std::string("InitOperationDialog.html");
		const std::string InitDataDialogUrl = DialogRootPath + std::string("InitDataDialog.html");
		const std::string AboutDialogUrl = DialogRootPath + std::string("AboutDialog.html");
	};

	namespace GUIResource
	{
		const std::string ResourcePath = SSUtils::File::InitailPath() + std::string("Resources") + SSUtils::File::PathSeperator();

		const std::string LoadingUrl = ResourcePath + std::string("Loading.gif");
	};
}
