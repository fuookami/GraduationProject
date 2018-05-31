#pragma once

#include <QtWidgets/QTreeWidget>
#include <memory>

namespace VEDA
{
	class VEDATreeView :public QTreeWidget
	{
		Q_OBJECT;

	public:
		explicit VEDATreeView(QWidget *parent = nullptr);
		VEDATreeView(const VEDATreeView &ano) = delete;
		VEDATreeView(VEDATreeView &&ano) = delete;
		VEDATreeView &operator=(const VEDATreeView &rhs) = delete;
		VEDATreeView &operator=(VEDATreeView &&rhs) = delete;
		~VEDATreeView(void) = default;
	};
};
