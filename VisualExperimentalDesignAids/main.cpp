#include <QtWidgets/QApplication>
#include "VEDAMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VEDA::VEDAMainWindow *w(new VEDA::VEDAMainWindow());
	w->show();
	return a.exec();
}
