#include "mainw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QString translatorFileName = "zh_CN.UTF-8.qm";
	QTranslator *trans = new QTranslator(&a);
	if(trans->load(translatorFileName)){
		a.installTranslator(trans);
	}

	MainW w;
	w.show();

	return a.exec();
}
