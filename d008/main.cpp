#include <QtWidgets/QApplication>
#include "d008.h"
#include "action.h"


int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	d008 w;
	w.init();
	w.show();
	return a.exec();
}
