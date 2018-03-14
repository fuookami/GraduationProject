#include "VEDAMainWindow.h"
#include "VEDAGlobal.h"
#include "VEDAVersion.h"
#include "QWebEngineWidget.h"
#include <QtWidgets/QMessageBox>

namespace VEDA
{
	VEDAMainWindow::VEDAMainWindow(QWidget * parent)
		: QMainWindow(parent), m_web(new QWebEngineWidget(this))
	{
		setMinimumSize(QSize(MinimumWidth, MinimumHeight));
		registerContents();
		m_web->load(QString::fromLocal8Bit(GUIEntrance.c_str()));

		connect(m_web->view(), &QWebEngineView::loadFinished, this, &VEDAMainWindow::onLoadFinished);
	}

	void VEDAMainWindow::resizeEvent(QResizeEvent * event)
	{
		m_web->setGeometry(0, 0, this->width(), this->height());
	}

	void VEDAMainWindow::onLoadFinished(bool ok)
	{
		if (!ok)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"),
				QString::fromLocal8Bit("无法打开GUI入口：%1，请确认是否错误。").arg(QString::fromLocal8Bit(GUIEntrance.c_str())));
			this->close();
		}
		else
		{
			initConnections();

			m_web->view()->page()->runJavaScript(QString("setVersion('%1');").arg(QString(Version.c_str())));
			m_web->view()->page()->runJavaScript(QString("setBuildDatetime('%1');").arg(QString(BuildDatetime.c_str())));
		}
	}

	void VEDAMainWindow::registerContents(void)
	{
	}

	void VEDAMainWindow::initConnections(void)
	{
	}
};
