#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include "CARSDK\ExperimentalDesignMethodModule.h"
#include "VEDAProcessFile.h"
#include "VEDAOperationFile.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	class VEDAInitOperationDialogInterface;

	class VEDAInitOperationDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width =780;
		static const int Height = 500;
		static const std::string DialogTitle;

	public:
		static VEDAInitOperationDialog *getInstance(VEDAProcessFile *processFile);

	private:
		VEDAInitOperationDialog(VEDAProcessFile *processFile);

	public:
		VEDAInitOperationDialog(const VEDAInitOperationDialog &ano) = delete;
		VEDAInitOperationDialog(VEDAInitOperationDialog &&ano) = delete;
		VEDAInitOperationDialog &operator=(const VEDAInitOperationDialog &rhs) = delete;
		VEDAInitOperationDialog &operator=(VEDAInitOperationDialog &&rhs) = delete;
		~VEDAInitOperationDialog(void) = default;

		inline const std::shared_ptr<VEDAInitOperationDialogInterface> interface(void) const { return m_interface; }

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		VEDAProcessFile *m_processFile;
		std::shared_ptr<VEDAInitOperationDialogInterface> m_interface;
	};

	class VEDAInitOperationDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAInitOperationDialog>
	{
		Q_OBJECT;
		friend class VEDAInitOperationDialog;

	private:
		explicit VEDAInitOperationDialogInterface(VEDAInitOperationDialog *dialog, VEDAProcessFile *processFile);

	public:
		VEDAInitOperationDialogInterface(const VEDAInitOperationDialogInterface &ano) = delete;
		VEDAInitOperationDialogInterface(VEDAInitOperationDialogInterface &&ano) = delete;
		VEDAInitOperationDialogInterface &operator=(const VEDAInitOperationDialogInterface &rhs) = delete;
		VEDAInitOperationDialogInterface &operator=(VEDAInitOperationDialogInterface &&rhs) = delete;
		~VEDAInitOperationDialogInterface(void) = default;

	signals:
		void savePathSelected(QString);
		void methodResponce(QString);
		void categoryResponce(QString);
		void attributeResponce(QString);
		void initOperationFailed(QString);
		void initOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	private:
		void emitMethodResponce(const QString &json);
		void emitCategoryResponce(const QString &json);
		void emitAttributeResponce(const QString &json);
	public:
		void emitInitOperationFailed(const QString &info);
		void emitInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	private:
		void onInitOperationSucceeded(std::shared_ptr<VEDAOperationFile>);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onMethodRequested(void);
		Q_INVOKABLE void onCategoryRequested(QJsonValue methodValue);
		Q_INVOKABLE void onAttributeRequested(QJsonValue methodValue, QJsonValue categoryValue);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue methodValue, QJsonValue categoryValue, QJsonValue attributeValues);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		VEDAProcessFile *m_processFile;
		std::shared_ptr<CARSDK::ExperimentalDesignMethodModule> m_methodModule;
	};
};
