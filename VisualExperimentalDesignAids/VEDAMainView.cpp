#include "VEDAMainView.h"
#include "VEDAHomeView.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils/GUI/QMessageBoxUtils.h"
#include <QtWidgets/QApplication>

namespace VEDA
{
	VEDAMainView::VEDAMainView(QWidget *parent)
		: QFrame(parent)
	{
		auto homeView = new VEDAHomeView(this);
		homeView->move(1, 1);
		m_currView = dynamic_cast<QWidget *>(homeView);
		connect(homeView, &VEDAHomeView::loadFinished, this, &VEDAMainView::onHomeViewLoadFinished);
	}

	void VEDAMainView::resizeEvent(QResizeEvent * event)
	{
		if (m_currView != nullptr)
		{
			m_currView->resize(this->width() - 2, this->height() - 2);
		}
	}

	void VEDAMainView::onHomeViewLoadFinished(bool ok, QString url)
	{
		if (!ok)
		{
			SSUtils::GUI::QMessageBoxUtils::information(QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�޷���GUI��ڣ�%1����ȷ���Ƿ����").arg(url));
			QApplication::exit();
		}
		else
		{
			emit loadingEnd();
		}
	}

	void VEDAMainView::onLoadingBegin(void)
	{
		emit loadingBegin();
	}

	void VEDAMainView::onLoadingEnd(void)
	{
		emit loadingEnd();
	}
}
