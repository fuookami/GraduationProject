#include "VEDAInitOperationDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGlobal.h"
#include "VEDAGUIGlobal.h"
#include "SSUtils\FileUtils.h"
#include <QtWidgets/QFileDialog>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <thread>

namespace VEDA
{
	const std::string VEDAInitOperationDialog::DialogTitle("新建实验操作");

	VEDAInitOperationDialog * VEDAInitOperationDialog::getInstance(VEDAProcessFile *processFile)
	{
		return new VEDAInitOperationDialog(processFile);
	}

	VEDAInitOperationDialog::VEDAInitOperationDialog(VEDAProcessFile *processFile)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitOperationDialogUrl.c_str()), nullptr),
		m_processFile(processFile), m_interface(new VEDAInitOperationDialogInterface(this, processFile))
	{
	}

	void VEDAInitOperationDialog::registerContents(void)
	{
		registerObject(m_interface);
	}

	void VEDAInitOperationDialog::initGUI(void)
	{
		m_view->page()->runJavaScript(QString("setPath('%1')")
			.arg(QString::fromLocal8Bit(SSUtils::File::getLinuxUrl(m_processFile->getPath()).c_str())));
	}

	VEDAInitOperationDialogInterface::VEDAInitOperationDialogInterface(VEDAInitOperationDialog *dialog, VEDAProcessFile *processFile)
		: IWebEngineDialogInterface(dialog), m_processFile(processFile), m_methodModule(CARSDK::ExperimentalDesignMethodModule::instance(PluginPath))
	{
		connect(this, &VEDAInitOperationDialogInterface::initOperationSucceeded, this, &VEDAInitOperationDialogInterface::onInitOperationSucceeded);
	}

	void VEDAInitOperationDialogInterface::emitMethodResponce(const QString & json)
	{
		emit methodResponce(json);
	}

	void VEDAInitOperationDialogInterface::emitCategoryResponce(const QString & json)
	{
		emit categoryResponce(json);
	}

	void VEDAInitOperationDialogInterface::emitAttributeResponce(const QString & json)
	{
		emit attributeResponce(json);
	}

	void VEDAInitOperationDialogInterface::emitInitOperationFailed(const QString & info)
	{
		emit initOperationFailed(info);
	}

	void VEDAInitOperationDialogInterface::emitInitOperationSucceeded(std::shared_ptr<VEDAOperationFile> operationFile)
	{
		emit initOperationSucceeded(operationFile);
	}

	void VEDAInitOperationDialogInterface::onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>)
	{
		m_dialog->close();
	}

	void VEDAInitOperationDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitOperationDialogInterface::onMethodRequested(void)
	{
		std::thread([this]()
		{
			this->m_methodModule->refreshUtils(PluginPath);

			QJsonObject json;

			for (const auto &pair : m_methodModule->utils())
			{
				json.insert(QString::fromLocal8Bit(pair.first.c_str()), QString::fromLocal8Bit(pair.second->displayName().c_str()));
			}

			QJsonDocument document;
			document.setObject(json);
			this->emitMethodResponce(QString(document.toJson(QJsonDocument::Compact)));
		}).detach();
	}

	void VEDAInitOperationDialogInterface::onCategoryRequested(QJsonValue methodValue)
	{
		std::string method(methodValue.toString().toLocal8Bit());
		auto methodUtil(m_methodModule->util(method));

		std::thread([this, methodUtil]()
		{
			QJsonObject json;

			for (const auto &pair : methodUtil->methods())
			{
				json.insert(QString::fromLocal8Bit(pair.first.c_str()), QString::fromLocal8Bit(pair.second->displayName().c_str()));
			}

			QJsonDocument document;
			document.setObject(json);
			this->emitCategoryResponce(QString(document.toJson(QJsonDocument::Compact)));
		}).detach();
	}

	void VEDAInitOperationDialogInterface::onAttributeRequested(QJsonValue methodValue, QJsonValue categoryValue)
	{
		static const QString NameTag("name");
		static const QString TypeTag("type");

		std::string method(methodValue.toString().toLocal8Bit());
		std::string category(categoryValue.toString().toLocal8Bit());
		auto methodUtil(m_methodModule->util(method));
		auto methodInterface(methodUtil->method(category));

		std::thread([this, methodInterface]()
		{
			QJsonObject json;

			for (const auto &pair : methodInterface->neededAttributes())
			{
				const auto &info = pair.second;

				QJsonObject attribute;
				attribute.insert(TypeTag, QString::fromLocal8Bit(CARSDK::AttributeType2String().left.find(info.second)->second.c_str()));
				attribute.insert(NameTag, QString::fromLocal8Bit(info.first.c_str()));
				json.insert(QString::fromLocal8Bit(pair.first.c_str()), attribute);
			}

			QJsonDocument document;
			document.setObject(json);
			this->emitAttributeResponce(QString(document.toJson(QJsonDocument::Compact)));
		}).detach();
	}

	void VEDAInitOperationDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue methodValue, QJsonValue categoryValue, QJsonValue attributeValues)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());
		std::string method(methodValue.toString().toLocal8Bit());
		std::string category(categoryValue.toString().toLocal8Bit());
		auto methodUtil(m_methodModule->util(method));
		auto methodInterface(methodUtil->method(category));

		std::thread([this, name, savePath, newDir, method, category, methodUtil, methodInterface, attributeValues]() 
		{
			auto attributesData = QJsonDocument::fromJson(attributeValues.toString().toLocal8Bit().data()).toVariant().toMap();
			auto attributesKey = attributesData.keys();

			std::map<std::string, std::string> attributes;
			for (const auto &key : attributesKey)
			{
				attributes.insert(std::make_pair(std::string(key.toLocal8Bit()), attributesData[key].toString().toLocal8Bit()));
			}

			auto ret = methodInterface->valid(attributes);
			if (!ret)
			{
				this->emitInitOperationFailed(QString::fromLocal8Bit(methodInterface->lastError().c_str()));
				return;
			}
			
			auto operationRet(VEDAProjectHandler::initOperation(this->m_processFile, name, savePath, newDir, method, category, attributes));
			if (!std::get<0>(operationRet))
			{
				this->emitInitOperationFailed(QString::fromLocal8Bit(std::get<1>(operationRet).c_str()));
			}
			else
			{
				auto operationFile(std::get<2>(operationRet));

				this->m_processFile->addDataFile(SSUtils::File::getRelativeUrlOfPath(this->m_processFile->getPath(), operationFile->getUrl()), operationFile);
				this->m_processFile->save();
				this->emitInitOperationSucceeded(operationFile);
			}
		}).detach();
	}

	void VEDAInitOperationDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
