#include "VEDAInitProjectDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGUIEnterence.h"
#include "QMessageBoxUtils.h"
#include <QtWidgets/QFileDialog>

namespace VEDA
{
	const std::string VEDAInitProjectDialog::DialogTitle("�½�ʵ����Ŀ");

	VEDAInitProjectDialog * VEDAInitProjectDialog::getInstance(void)
	{
		return new VEDAInitProjectDialog();
	}

	VEDAInitProjectDialog::VEDAInitProjectDialog(void)
		: IWebEngineDialogWidget(QString::fromLocal8Bit(GUIEntrance::InitProjectDialogUrl.c_str()), nullptr), m_interface(new VEDAInitProjectDialogInterface(this))
	{
	}

	void VEDAInitProjectDialog::registerContents(void)
	{
		m_webWidget->registerObject(m_interface);
	}

	void VEDAInitProjectDialog::initGUI(void)
	{
	}

	VEDAInitProjectDialogInterface::VEDAInitProjectDialogInterface(VEDAInitProjectDialog * dialog)
		: IWebEngineDialogInterface(dialog)
	{
		connect(this, &VEDAInitProjectDialogInterface::initProjectSucceeded, this, &VEDAInitProjectDialogInterface::onInitProjectSucceeded);
	}

	void VEDAInitProjectDialogInterface::emitInitProjectFailed(const QString & info)
	{
		emit initProjectFailed(info);
	}

	void VEDAInitProjectDialogInterface::emitInitProjectSucceeded(const std::string &newProjectUrl)
	{
		emit initProjectSucceeded(newProjectUrl);
	}

	void VEDAInitProjectDialogInterface::onInitProjectSucceeded(std::string newProjectUrl)
	{
		m_dialog->close();

		auto projectHandler(VEDAProjectHandler::getInstance());
		if (projectHandler->isProjectOpen())
		{
			static const QString Title(QString::fromLocal8Bit("���½�ʵ����Ŀ"));
			static const QString Information(QString::fromLocal8Bit("�Ƿ�Ҫ���½���ʵ����Ŀ��"));
			if (QMessageBoxUtils::yesOrNot(Title, Information))
			{
				projectHandler->openProject(newProjectUrl);
			}

		}
		else
		{
			static const QString Title(QString::fromLocal8Bit("���½�ʵ����Ŀ"));
			static const QString Information(QString::fromLocal8Bit("�Ƿ�Ҫ�رղ����浱ǰ��Ŀ��Ȼ����½���ʵ����Ŀ��"));
			static const QString Button1Text(QString::fromLocal8Bit("ȷ��"));
			static const QString Button2Text(QString::fromLocal8Bit("�رյ�������"));
			int selected(QMessageBoxUtils::tricomfirm(Title, Information, Button1Text, Button2Text));
			if (selected == 1)
			{
				projectHandler->openProject(newProjectUrl);
			}
			else if (selected == 2)
			{
				projectHandler->openProject(newProjectUrl, false);
			}
		}
	}

	void VEDAInitProjectDialogInterface::onSelectSavePathBtnClicked(void)
	{
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("ѡ�񱣴�λ��"), QString("")));
		if (!selectedPath.isEmpty())
		{
			emit savePathSelected(selectedPath);
		}
	}

	void VEDAInitProjectDialogInterface::onConfirmBtnClicked(QJsonValue nameValue, QJsonValue savePathValue, bool newDir)
	{
		std::string name(nameValue.toString().toLocal8Bit());
		std::string savePath(savePathValue.toString().toLocal8Bit());

		if (name.empty() || savePath.empty())
		{
			this->emitInitProjectFailed(QString::fromLocal8Bit("��Ŀ���ƺ���Ŀ�洢λ�ò���Ϊ�ա�"));
		}
		else
		{
			std::thread([this, name, savePath, newDir]() 
			{
				auto ret(VEDAProjectHandler::initProject(name, savePath, newDir));
				if (!ret.first)
				{
					this->emitInitProjectFailed(QString::fromLocal8Bit(ret.second.c_str()));
				}
				else
				{
					this->emitInitProjectSucceeded(ret.second);
				}
			}).detach();
		}
	}

	void VEDAInitProjectDialogInterface::onCancelBtnClicked(void)
	{
		m_dialog->close();
	}
};
