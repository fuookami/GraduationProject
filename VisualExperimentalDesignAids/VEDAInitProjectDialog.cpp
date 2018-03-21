#include "VEDAInitProjectDialog.h"
#include "VEDAProjectHandler.h"
#include "QMessageBoxUtils.h"
#include "ui_VEDAInitProjectDialog.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

namespace VEDA
{
	std::shared_ptr<VEDAInitProjectDialog> VEDAInitProjectDialog::getInstance(void)
	{
		std::shared_ptr<VEDAInitProjectDialog> instance(new VEDAInitProjectDialog());
		return instance;
	}

	VEDAInitProjectDialog::VEDAInitProjectDialog(void)
		: QDialog(nullptr), m_ui(new Ui::VEDAInitProjectDialog())
	{
		m_ui->setupUi(this);

		connect(m_ui->SelectLocationBtn, &QPushButton::clicked, this, &VEDAInitProjectDialog::onSelectLocationBtnClicked);
		connect(m_ui->ComfirmBtn, &QPushButton::clicked, this, &VEDAInitProjectDialog::onComfirmBtnClicked);
		connect(m_ui->CancelBtn, &QPushButton::clicked, this, &VEDAInitProjectDialog::onCancelBtnClicked);
	}

	void VEDAInitProjectDialog::onSelectLocationBtnClicked(void)
	{
		QString location = QFileDialog::getExistingDirectory(nullptr, QString::fromLocal8Bit("项目位置"), QString(""));
		if (!location.isEmpty())
		{
			m_ui->ProjectLocation->setText(location);
		}
	}

	void VEDAInitProjectDialog::onComfirmBtnClicked(void)
	{
		if (m_ui->ProjectName->text().isEmpty() || m_ui->ProjectLocation->text().isEmpty())
		{
			static const QString Information(QString::fromLocal8Bit("项目名称和项目存储位置不能为空。"));
			m_ui->Infomation->setText(Information);
		}
		else
		{
			auto ret(VEDAProjectHandler::initProject(std::string(m_ui->ProjectName->text().toLocal8Bit()), 
				std::string(m_ui->ProjectLocation->text().toLocal8Bit()), m_ui->ToInitNewDir->isChecked()));
			if (!ret.first)
			{
				static const QString Title(QString::fromLocal8Bit("新建实验项目"));
				static const QString Information(QString::fromLocal8Bit("新建实验项目失败： %1"));
				QString info(QString::fromLocal8Bit(ret.second.c_str()));
				QMessageBox::information(nullptr, Title, Information.arg(info));
				m_ui->Infomation->setText(info);
			}
			else
			{
				auto projectHandler(VEDAProjectHandler::getInstance());
				if (projectHandler->isProjectOpen())
				{
					static const QString Title(QString::fromLocal8Bit("打开新建实验项目"));
					static const QString Information(QString::fromLocal8Bit("是否要打开新建的实验项目？"));
					if (QMessageBoxUtils::yesOrNot(Title, Information))
					{
						projectHandler->openProject(ret.second);
					}
					this->close();
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
						projectHandler->openProject(ret.second);
					}
					else if (selected == 2)
					{
						projectHandler->openProject(ret.second, false);
					}
					this->close();
				}
			}
		}
	}

	void VEDAInitProjectDialog::onCancelBtnClicked(void)
	{
		this->close();
	}
};
