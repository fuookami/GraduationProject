#include "VEDADataView.h"
#include "VEDAGUIGlobal.h"

namespace VEDA
{
	VEDADataView::VEDADataView(VEDADataFile * file, QWidget * parent)
		: QWebEngineWidget(parent), m_file(file), m_interface(new VEDADataViewInterface(file, this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::DataViewUrl.c_str()));
	}


	VEDADataViewInterface::VEDADataViewInterface(VEDADataFile * file, VEDADataView * widget)
		: IWebEngineWidgetInterface(widget), m_file(file)
	{
	}

	void VEDADataViewInterface::dataRequested(void)
	{
		// to do
	}

	void VEDADataViewInterface::dataSubmit(QJsonValue dataValue)
	{
		// to do
	}
};
