#include "VEDAInitProjectDialog.h"
#include "VEDAProjectHandler.h"
#include "VEDAGUIEnterence.h"
#include "QMessageBoxUtils.h"
#include <QtWidgets/QFileDialog>

namespace VEDA
{
	const std::string VEDAInitProjectDialog::DialogTitle("新建实验项目");

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
			static const QString Title(QString::fromLocal8Bit("打开新建实验项目"));
			static const QString Information(QString::fromLocal8Bit("是否要打开新建的实验项目？"));
			if (QMessageBoxUtils::yesOrNot(Title, Information))
			{
				projectHandler->openProject(newProjectUrl);
			}

		}
		else
		{
			static const QString Title(QString::fromLocal8Bit("打开新建实验项目"));
			static const QString Information(QString::fromLocal8Bit("是否要关闭并保存当前项目，然后打开新建的实验项目？"));
			static const QString Button1Text(QString::fromLocal8Bit("确定"));
			static const QString Button2Text(QString::fromLocal8Bit("关闭但不保存"));
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
		QString selectedPath(QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("选择保存位置"), QString("")));
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
			this->emitInitProjectFailed(QString::fromLocal8Bit("项目名称和项目存储位置不能为空。"));
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
