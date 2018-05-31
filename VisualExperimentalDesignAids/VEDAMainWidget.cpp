#include "VEDAMainWidget.h"
#include <QtWidgets/QHBoxLayout>

namespace VEDA
{
	const int VEDAMainWidget::TreeViewWidth = 250;
	const int VEDAMainWidget::Space = 5;
	const int VEDAMainWidget::MainViewMinimumWidth = 992;

	VEDAMainWidget::VEDAMainWidget(void)
		: QWidget(nullptr), m_treeView(nullptr), m_mainView(nullptr)
	{
	}

	void VEDAMainWidget::init(void)
	{
		m_treeView = new VEDATreeView();
		m_mainView = new VEDAMainView();

		auto layout = new QHBoxLayout();
		layout->addWidget(m_treeView);
		layout->addWidget(m_mainView);
		layout->setSpacing(Space);

		m_treeView->setMinimumWidth(TreeViewWidth);
		m_treeView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		m_mainView->setMinimumWidth(MainViewMinimumWidth);
		m_mainView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

		this->setLayout(layout);
		m_mainView->setStyleSheet(QString::fromLocal8Bit("QFrame{ border-style: solid; border-width: 1px; border-color: darkGray;}"));

		initConnections();
	}

	void VEDAMainWidget::initConnections(void)
	{
		connect(m_mainView, &VEDAMainView::loadingBegin, this, &VEDAMainWidget::onLoadingBegin);
		connect(m_mainView, &VEDAMainView::loadingEnd, this, &VEDAMainWidget::onLoadingEnd);
	}

	void VEDAMainWidget::onLoadingBegin(void)
	{
		emit loadingBegin();
	}

	void VEDAMainWidget::onLoadingEnd(void)
	{
		emit loadingEnd();
	}
};
