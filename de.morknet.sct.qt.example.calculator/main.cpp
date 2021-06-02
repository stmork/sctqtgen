#include "mainwindow.h"
#include <QApplication>

int main(int argc, char * argv[])
{
	QApplication a(argc, argv);
	QIcon icon(":AppIcon");
	MainWindow w;

	w.setWindowIcon(icon);
	w.show();

	return a.exec();
}
