#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include "CARSDK\ExperimentalAnalyzerModule.h"
#include "VEDAProcessFile.h"
#include "VEDAOperationFile.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	/*
	class VEDAInitOperationDialogInterface;

	class VEDAInitOperationDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;

	public:
		static VEDAInitOperationDialog *getInstance(const std::shared_ptr<VEDAProcessFile> processFile);

	private:
		VEDAInitOperationDialog(const std::shared_ptr<VEDAProcessFile> processFile);

	public:
		VEDAInitOperationDialog(const VEDAInitOperationDialog &ano) = delete;
		VEDAInitOperationDialog(VEDAInitOperationDialog &&ano) = delete;
		VEDAInitOperationDialog &operator=(const VEDAInitOperationDialog &rhs) = delete;
		VEDAInitOperationDialog &operator=(VEDAInitOperationDialog &&rhs) = delete;
		~VEDAInitOperationDialog(void) = default;

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		std::shared_ptr<VEDAProcessFile> m_processFile;
		std::shared_ptr<VEDAInitOperationDialogInterface> m_interface;
	};

	class VEDAInitOperationDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAInitOperationDialog>
	{
		Q_OBJECT;
		friend class VEDAInitOperationDialog;

	private:
		explicit VEDAInitOperationDialogInterface(VEDAInitOperationDialog *dialog, const std::shared_ptr<VEDAProcessFile> processFile);

	public:
		VEDAInitOperationDialogInterface(const VEDAInitOperationDialogInterface &ano) = delete;
		VEDAInitOperationDialogInterface(VEDAInitOperationDialogInterface &&ano) = delete;
		VEDAInitOperationDialogInterface &operator=(const VEDAInitOperationDialogInterface &rhs) = delete;
		VEDAInitOperationDialogInterface &operator=(VEDAInitOperationDialogInterface &&rhs) = delete;
		~VEDAInitOperationDialogInterface(void) = default;

	signals:
		void methodResponce(QString);
		void categoryResponce(QString);
		void attributeResponce(QString);
		void initOperationFailed(QString);
		void inttOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	public:
		void emitInitOperationFailed(const QString &info);
		void emitInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	private:
		void onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onMethodRequested(void);
		Q_INVOKABLE void onCategoryRequested(QJsonValue method);
		Q_INVOKABLE void onAttributeRequested(QJsonValue method, QJsonValue category);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue method, QJsonValue category, QJsonValue attributes);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		std::shared_ptr<CARSDK::ExperimentalDesignMethodModule> m_methodModule;
	};
	*/
};
