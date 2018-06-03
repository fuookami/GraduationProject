#pragma once

#include "SSUtils\GUI\IWebEngineDialogWidget.h"
#include "VEDAProcessFile.h"
#include "VEDAModelFile.h"
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include <memory>

namespace VEDA
{
	class VEDAInitModelDialogInterface;

	class VEDAInitModelDialog final : public SSUtils::GUI::IWebEngineDialogWidget
	{
		static const int Width = 650;
		static const int Height = 375;
		static const std::string DialogTitle;

	public:
		static VEDAInitModelDialog *getInstance(VEDAProcessFile *processFile);

	private:
		VEDAInitModelDialog(VEDAProcessFile *processFile);

	public:
		VEDAInitModelDialog(const VEDAInitModelDialog &ano) = delete;
		VEDAInitModelDialog(VEDAInitModelDialog &&ano) = delete;
		VEDAInitModelDialog &operator=(const VEDAInitModelDialog &rhs) = delete;
		VEDAInitModelDialog &operator=(VEDAInitModelDialog &&rhs) = delete;
		~VEDAInitModelDialog(void) = default;

		inline const std::shared_ptr<VEDAInitModelDialogInterface> interface(void) const { return m_interface; }

	protected:
		void registerContents(void) override;
		void initGUI(void) override;

	private:
		VEDAProcessFile * m_processFile;
		std::shared_ptr<VEDAInitModelDialogInterface> m_interface;
	};

	class VEDAInitModelDialogInterface : public SSUtils::GUI::IWebEngineWidgetInterface<VEDAInitModelDialog>
	{
		Q_OBJECT;
		friend class VEDAInitModelDialog;

	private:
		explicit VEDAInitModelDialogInterface(VEDAInitModelDialog *dialog, VEDAProcessFile *processFile);

	public:
		VEDAInitModelDialogInterface(const VEDAInitModelDialogInterface &ano) = delete;
		VEDAInitModelDialogInterface(VEDAInitModelDialogInterface &&ano) = delete;
		VEDAInitModelDialogInterface &operator=(const VEDAInitModelDialogInterface &rhs) = delete;
		VEDAInitModelDialogInterface &operator=(VEDAInitModelDialogInterface &&rhs) = delete;
		~VEDAInitModelDialogInterface(void) = default;

	signals:
		void savePathSelected(QString);
		void initModelFailed(QString);
		void initModelSucceeded(std::shared_ptr<VEDAModelFile>);

	public:
		void emitInitModelFailed(const QString *info);
		void emitInitModelSucceeded(std::shared_ptr<VEDAModelFile>);

	private:
		void onInitModelSucceeded(std::shared_ptr<VEDAModelFile>);

	public:
		Q_INVOKABLE void onSelectSavePathBtnClicked(void);
		Q_INVOKABLE void onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue);
		Q_INVOKABLE void onCancelBtnClicked(void);

	private:
		VEDAProcessFile * m_processFile;
	};
};
