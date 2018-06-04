#include "VEDAAnalysisView.h"
#include "VEDAGUIGlobal.h"

namespace VEDA
{
	VEDAAnalysisView::VEDAAnalysisView(VEDADataFile * file, QWidget * parent)
		: QWebEngineWidget(parent), m_file(file), m_interface(new VEDAAnalysisViewInterface(file, this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::AnalysisViewUrl.c_str()));
	}


	VEDAAnalysisViewInterface::VEDAAnalysisViewInterface(VEDADataFile * file, VEDAAnalysisView * widget)
		: IWebEngineWidgetInterface(widget), m_file(file)
	{
	}
	
	void VEDAAnalysisViewInterface::analyzerRequested(void)
	{
	}

	void VEDAAnalysisViewInterface::analysisRequested(QJsonValue analyzerValue)
	{
	}
};
