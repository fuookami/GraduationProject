#include "VEDAAnalysisView.h"
#include "VEDAGUIGlobal.h"
#include "VEDAProcessFile.h"
#include "VEDAOperationFile.h"
#include "CARSDK\ExperimentalAnalyzerModule.h"
#include "CARSDK\ExperimentalAnalyzerUtilsInterface.h"
#include "CARSDK\ExperimentalAnalyzerInterface.h"
#include "VEDAProjectHandler.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <thread>

namespace VEDA
{
	VEDAAnalysisView::VEDAAnalysisView(VEDADataFile * file, QWidget * parent)
		: QWebEngineWidget(parent), m_file(file), m_interface(new VEDAAnalysisViewInterface(file, this))
	{
		registerObject(m_interface);

		load(QString::fromLocal8Bit(GUIEntrance::AnalysisViewUrl.c_str()));
	}


	VEDAAnalysisViewInterface::VEDAAnalysisViewInterface(VEDADataFile * file, VEDAAnalysisView * widget)
		: IWebEngineWidgetInterface(widget), m_file(file)
	{
	}
	
	void VEDAAnalysisViewInterface::emitAnalyzerResponse(const bool ok, const QString & data)
	{
		emit analyzerResponse(ok, data);
	}

	void VEDAAnalysisViewInterface::emitAnalysisResponse(const bool ok, const QString & data)
	{
		emit analysisResponse(ok, data);
	}

	void VEDAAnalysisViewInterface::analyzerRequested(void)
	{
		std::thread([this]()
		{
			auto dataFile(this->m_file);
			auto operationFile(dataFile->getParent());
			auto processFile(operationFile->getParent());
			auto projectHandler = VEDAProjectHandler::getInstance();

			projectHandler->emitLoadingBegin();
			this->m_data = CARSDK::DataHandlingModule::instance()->analyze(dataFile->getModel(), dataFile->getData());
			this->m_factors = CARSDK::DataModelingModule::instance()->analyzeForData(dataFile->getModel());
			this->m_group = CARSDK::DataModelingModule::divideToGroup(this->m_factors);
			if (this->m_data.empty())
			{
				this->emitAnalyzerResponse(false, QString::fromLocal8Bit("解析数据文件失败"));
				return;
			}

			auto AnalyzerModule(CARSDK::ExperimentalAnalyzerModule::instance());
			auto AnalyzerUtils(AnalyzerModule->util(operationFile->getDesignMethodName()));
			if (AnalyzerUtils == nullptr)
			{
				this->emitAnalyzerResponse(false, QString::fromLocal8Bit("没有找到实验设计方法工具集：%1").arg(QString::fromLocal8Bit(operationFile->getDesignMethodName().c_str())));
				return;
			}
			auto AnalyzerInterface(AnalyzerUtils->analyzerGroup(operationFile->getDesignMethodCategory()));
			if (AnalyzerInterface == nullptr)
			{
				this->emitAnalyzerResponse(false, QString::fromLocal8Bit("在%1中找不到实验设计方法类别%2的分析方法").arg(QString::fromLocal8Bit(AnalyzerInterface->displayName().c_str())).arg(QString::fromLocal8Bit(operationFile->getDesignMethodCategory().c_str())));
				return;
			}
			this->m_analyzers = AnalyzerInterface->generateAnalyzerGroup(this->m_group);

			QJsonObject json;
			QJsonArray analyzers;
			
			for (const auto &flag : this->m_analyzers.flags)
			{
				static const QString NameTag("name");
				static const QString DisplayTag("display");

				QJsonObject analyzer;
				analyzer.insert(NameTag, QString::fromLocal8Bit(flag.first.c_str()));
				analyzer.insert(DisplayTag, QString::fromLocal8Bit(flag.second.c_str()));
				analyzers.push_back(analyzer);
			}

			json.insert("analyzers", analyzers);
			QJsonDocument document;
			document.setObject(json);
			this->emitAnalyzerResponse(true, QString(document.toJson(QJsonDocument::Compact)));
			projectHandler->emitLoadingEnd();
		}).detach();
	}

	void VEDAAnalysisViewInterface::analysisRequested(QJsonValue analyzerValue)
	{
		std::string flag(analyzerValue.toString().toLocal8Bit());

		std::thread([this, flag]()
		{
			auto dataFile(this->m_file);
			auto operationFile(dataFile->getParent());
			auto projectHandler = VEDAProjectHandler::getInstance();

			projectHandler->emitLoadingBegin();

			auto result = this->m_analyzers.analyze(this->m_group, this->m_data, operationFile->getAttributes(), flag);

			QJsonObject json;
			
			json.insert("type", QString::fromLocal8Bit(CARSDK::AnalysisResultType2String().left.find(result.first)->second.c_str()));
			json.insert("data", QString::fromLocal8Bit(result.second.c_str()));

			QJsonDocument document;
			document.setObject(json);
			this->emitAnalysisResponse(true, QString(document.toJson(QJsonDocument::Compact)));
			projectHandler->emitLoadingEnd();
		}).detach();
	}
};
