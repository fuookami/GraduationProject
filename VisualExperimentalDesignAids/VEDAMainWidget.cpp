#include "VEDAMainWidget.h"
#include <QtWidgets/QHBoxLayout>

namespace VEDA
{
	VEDAMainWidget::VEDAMainWidget(void)
		: QWidget(nullptr), m_treeView(new VEDATreeView()), m_mainView(new VEDAMainView())
	{
		auto layout = new QHBoxLayout();
		layout->addWidget(m_treeView);
		layout->addWidget(m_mainView);
		layout->setSpacing(5);
		layout->setStretch(0, 3);
		layout->setStretch(1, 7);
		this->setLayout(layout);

		resizeEvent(nullptr);
	}

	void VEDAMainWidget::resizeEvent(QResizeEvent * e)
	{
		m_mainView->resize(this->width() * 0.614, this->height());
	}
};
