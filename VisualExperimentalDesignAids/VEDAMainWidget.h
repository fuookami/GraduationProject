#pragma once

#include "VEDAMainView.h"
#include "VEDATreeView.h"

namespace VEDA
{
	class VEDAMainWidget : public QWidget
	{
		Q_OBJECT;

	public:
		static const int TreeViewWidth;
		static const int Space;
		static const int MainViewMinimumWidth;

	public:
		explicit VEDAMainWidget(void);
		VEDAMainWidget(const VEDAMainWidget &ano) = delete;
		VEDAMainWidget(VEDAMainWidget &&ano) = delete;
		VEDAMainWidget &operator=(const VEDAMainWidget &rhs) = delete;
		VEDAMainWidget &operator=(VEDAMainWidget &&rhs) = delete;
		~VEDAMainWidget(void) = default;

		inline VEDATreeView *getTreeView(void) { return m_treeView; }
		inline const VEDATreeView *getTreeView(void) const { return m_treeView; }
		inline VEDAMainView *getMainView(void) { return m_mainView; }
		inline const VEDAMainView *getMainView(void) const { return m_mainView; }

		void init(void);

	private:
		void initConnections(void);

	signals:
		void loadingBegin(void);
		void loadingEnd(void);

	private:
		void onLoadingBegin(void);
		void onLoadingEnd(void);

	private:
		VEDATreeView *m_treeView;
		VEDAMainView *m_mainView;
	};
};
