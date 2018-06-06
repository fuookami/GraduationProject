#include "VEDAMainView.h"
#include "VEDAHomeView.h"
#include "VEDAModelView.h"
#include "VEDADataView.h"
#include "VEDAAnalysisView.h"
#include "VEDAGUIGlobal.h"
#include "VEDAMainView.h"
#include "VEDAProjectHandler.h"
#include "SSUtils/GUI/QMessageBoxUtils.h"
#include <QtWidgets/QApplication>

namespace VEDA
{
	VEDAMainView::VEDAMainView(QWidget *parent)
		: QFrame(parent), m_currFile(nullptr), m_type(Type::Home)
	{
		auto homeView = new VEDAHomeView(this);
		homeView->move(1, 1);
		m_currView = dynamic_cast<QWidget *>(homeView);
		connect(homeView, &VEDAHomeView::loadFinished, this, &VEDAMainView::onHomeViewLoadFinished);
		connect(VEDAProjectHandler::getInstance().get(), &VEDAProjectHandler::closeProjectFinished, this, &VEDAMainView::onProjectClosed);
	}

	void VEDAMainView::resizeEvent(QResizeEvent * event)
	{
		if (m_currView != nullptr)
		{
			m_currView->resize(this->width() - 2, this->height() - 2);
		}
	}

	void VEDAMainView::onModelOpened(VEDAModelFile * modelFile)
	{
		if (m_currFile != modelFile || m_type != Type::Model)
		{
			closeCurrentView();
		}

		m_currFile = modelFile;
		m_type = Type::Model;
		refreshCurrentView(new VEDAModelView(modelFile, this));
	}

	void VEDAMainView::onModelRemove(std::shared_ptr<VEDAModelFile> modelFile)
	{
		if (m_currFile == modelFile.get())
		{
			closeCurrentView();
		}
	}

	void VEDAMainView::onDataOpened(VEDADataFile * dataFile)
	{
		if (m_currFile != dataFile || m_type != Type::Data)
		{
			closeCurrentView();
		}

		m_currFile = dataFile;
		m_type = Type::Data;
		refreshCurrentView(new VEDADataView(dataFile, this));
	}

	void VEDAMainView::onDataRemove(std::shared_ptr<VEDADataFile> dataFile)
	{
		if (m_currFile == dataFile.get())
		{
			closeCurrentView();
		}
	}

	void VEDAMainView::onDataAnalyzerOpened(VEDADataFile * dataFile)
	{
		if (m_currFile != dataFile || m_type != Type::Analysis)
		{
			closeCurrentView();
		}

		m_currFile = dataFile;
		m_type = Type::Analysis;
		refreshCurrentView(new VEDAAnalysisView(dataFile, this));
	}

	void VEDAMainView::onHomeViewLoadFinished(bool ok, QString url)
	{
		if (!ok)
		{
			SSUtils::GUI::QMessageBoxUtils::information(QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("无法打开GUI入口：%1，请确认是否错误。").arg(url));
			QApplication::exit();
		}
		else
		{
			emit loadingEnd();
		}
	}

	void VEDAMainView::onProjectClosed(bool ok, QString)
	{
		if (ok)
		{
			if (m_type != Type::Home)
			{
				closeCurrentView();
			}

			m_currFile = nullptr;
			m_type = Type::Home;
			refreshCurrentView(new VEDAHomeView(this));
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

	void VEDAMainView::refreshCurrentView(QWidget * view)
	{
		m_currView = view;
		m_currView->move(1, 1);
		m_currView->resize(this->width() - 2, this->height() - 2);
		m_currView->show();
	}

	void VEDAMainView::closeCurrentView(void)
	{
		m_currView->deleteLater();
		m_currView = nullptr;
		m_currFile = nullptr;
	}
}
