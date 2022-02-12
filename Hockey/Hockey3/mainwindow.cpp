#include "mainwindow.h"
#include <QApplication>
QMenu* file;
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	w = new Breakout(this);
	player = new QMediaPlayer(this);
	player1 = new QMediaPlayer(this);
	player->setMedia(QUrl("crowd.mp3"));
	player1->setMedia(QUrl("music.mp3"));
	player->setVolume(30);
	player1->setVolume(30);
	player->play();
	player1	->play();

	w->flag = 0;
	setCentralWidget(w);
	w->setFocus();
}

MainWindow::~MainWindow()
{
}