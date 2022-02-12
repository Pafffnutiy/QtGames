#include "mainwindow.h"

#include <QApplication>
#include <QtMultimedia/qmediaplayer.h>
#include <D:\\QT\5.12.11\msvc2017_64\include\QtMultimedia\QMediaPlayer>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}