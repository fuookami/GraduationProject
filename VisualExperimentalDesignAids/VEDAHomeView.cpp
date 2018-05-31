#include "VEDAHomeView.h"
#include "VEDAGUIGlobal.h"

namespace VEDA
{
	VEDAHomeView::VEDAHomeView(QWidget * parent)
		: QWebEngineWidget(parent), m_interface(new VEDAHomeViewInterface(this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::HomeViewUrl.c_str()));
	}

	VEDAHomeViewInterface::VEDAHomeViewInterface(VEDAHomeView * widget)
		: IWebEngineWidgetInterface(widget)
	{
	}
};
