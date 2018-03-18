#include <QtWidgets/QApplication>
#include "VEDAMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	auto w(VEDA::VEDAMainWindow::getInstance());
	w->show();
	return a.exec();
}
