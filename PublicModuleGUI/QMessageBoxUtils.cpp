#include "QMessageBoxUtils.h"
#include <QtWidgets/QMessageBox>

namespace  QMessageBoxUtils
{
	void information(const QString & title, const QString & information)
	{
	}

	bool comfirm(const QString & title, const QString & information)
	{
		return false;
	}

	bool yesOrNot(const QString & title, const QString & information)
	{
		return false;
	}

	int tricomfirm(const QString & title, const QString & information, const QString & button1Text, const QString & button2Text)
	{
		return 0;
	}

	int dualSelect(const QString & title, const QString & information, const QString & button1Tect, const QString & button2Text)
	{
		return 0;
	}

	int triSelect(const QString & title, const QString & information, const QString & button1Text, const QString & button2Text, const QString & button3Text)
	{
		return 0;
	}
};
