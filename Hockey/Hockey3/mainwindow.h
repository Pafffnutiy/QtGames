#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "breakout.h"
#include <QMainWindow>
#include <QtMultimedia/qmediaplayer.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	QMediaPlayer* player;
	QMediaPlayer* player1;
	Breakout* w;

};
#endif // MAINWINDOW_H
