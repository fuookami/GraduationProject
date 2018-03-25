#include "IWebEngineDialogWidget.h"
#include <QtCore/QDebug>
#include "QWebEngineWidget.h"

IWebEngineDialogWidget::IWebEngineDialogWidget(const QString &guiEntrance, QWidget * parent)
	: QWidget(parent), m_guiEntrance(guiEntrance), m_webWidget(new QWebEngineWidget(this))
{
	m_web = m_webWidget->view();
	setAttribute(Qt::WA_ShowModal, true);
}

void IWebEngineDialogWidget::resizeEvent(QResizeEvent * event)
{
	m_webWidget->setGeometry(0, 0, this->width(), this->height());
}

void IWebEngineDialogWidget::showEvent(QShowEvent * event)
{
	registerContents();
	m_webWidget->load(m_guiEntrance);

	connect(m_web, &QWebEngineView::loadFinished, this, &IWebEngineDialogWidget::onLoadFinished);
}

void IWebEngineDialogWidget::closeEvent(QCloseEvent * event)
{
	this->deleteLater();
}

void IWebEngineDialogWidget::onLoadFinished(bool ok)
{
	if (!ok)
	{
		qDebug() << QString::fromLocal8Bit("无法打开GUI入口: ") << m_guiEntrance;
	}
	else
	{
		initGUI();
	}
}
