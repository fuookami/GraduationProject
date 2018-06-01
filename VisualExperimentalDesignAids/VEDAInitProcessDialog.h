#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include "VEDAProjectFile.h"
#include "VEDAProcessFile.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	class VEDAInitProcessDialogInterface;

	class VEDAInitProcessDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;

	public:
		static VEDAInitProcessDialog *getInstance(VEDAProjectFile *projectFile);

	private:
		VEDAInitProcessDialog(VEDAProjectFile *projectFile);
	public:
		VEDAInitProcessDialog(const VEDAInitProcessDialog &ano) = delete;
		VEDAInitProcessDialog(VEDAInitProcessDialog &&ano) = delete;
		VEDAInitProcessDialog &operator=(const VEDAInitProcessDialog &rhs) = delete;
		VEDAInitProcessDialog &operator=(VEDAInitProcessDialog &&rhs) = delete;
		~VEDAInitProcessDialog(void) = default;

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		VEDAProjectFile *m_projectFile;
		std::shared_ptr<VEDAInitProcessDialogInterface> m_interface;
	};

	class VEDAInitProcessDialogInterface : public SSUtils::GUI::IWebEngineDialogInterface<VEDAInitProcessDialog>
	{
		Q_OBJECT;
		friend class VEDAInitProcessDialog;

	private:
		explicit VEDAInitProcessDialogInterface(VEDAInitProcessDialog *dialog, VEDAProjectFile *projectFile);

	public:
		VEDAInitProcessDialogInterface(const VEDAInitProcessDialogInterface &ano) = delete;
		VEDAInitProcessDialogInterface(VEDAInitProcessDialogInterface &&ano) = delete;
		VEDAInitProcessDialogInterface &operator=(const VEDAInitProcessDialogInterface &rhs) = delete;
		VEDAInitProcessDialogInterface &operator=(VEDAInitProcessDialogInterface &&rhs) = delete;
		~VEDAInitProcessDialogInterface(void) = default;

	signals:
		void savePathSelected(QString);
		void initProcessFailed(QString);
		void initProcessSucceeded(std::shared_ptr<VEDAProcessFile>);

	public:
		void emitInitProcessFailed(const QString &info);
		void emitInitProcessSucceeded(std::shared_ptr<VEDAProcessFile>);

	private:
		void onInitProcessSucceeded(std::shared_ptr<VEDAProcessFile>);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir);
		Q_INVOKABLE void onConfirmBtnClickedWithModel(QJsonValue nameValue, QJsonValue savePathValue, bool newDir, QJsonValue modelNameValue);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		VEDAProjectFile *m_projectFile;
	};
};
