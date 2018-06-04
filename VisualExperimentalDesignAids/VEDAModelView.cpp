#include "VEDAModelView.h"
#include "VEDAGUIGlobal.h"

namespace VEDA
{
	VEDAModelView::VEDAModelView(VEDAModelFile * file, QWidget * parent)
		: QWebEngineWidget(parent), m_file(file), m_interface(new VEDAModelViewInterface(file, this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::ModelViewUrl.c_str()));
	}


	VEDAModelViewInterface::VEDAModelViewInterface(VEDAModelFile * file, VEDAModelView * widget)
		: IWebEngineWidgetInterface(widget), m_file(file)
	{
	}

	void VEDAModelViewInterface::dataRequested(void)
	{
		// to do
	}

	void VEDAModelViewInterface::dataSubmit(QJsonValue dataValue)
	{
		// to do
	}
};
