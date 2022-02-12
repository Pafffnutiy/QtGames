#include "mainwindow.h"
#include <QtMultimedia/qmediaplayer.h>
#include <D:\\QT\5.12.11\msvc2017_64\include\QtMultimedia\QMediaPlayer>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	Pool = new Widget();
	MainWindow::setCentralWidget(Pool);
	setFixedSize(1120, 630);
	player = new QMediaPlayer(this);

	//player->setMedia(QUrl("club.mp3"));
	//player->setVolume(30);
	//player->play();

	setStyleSheet("background-color:gradient");
}

MainWindow::~MainWindow()
{
	delete ui;
}

Widget::Widget(QWidget* parent) : QWidget(parent) {
	ball[0].BallPoint.setX(825);
	ball[0].BallPoint.setY(375);

	ball[1].BallPoint.setX(375 + 30);
	ball[1].BallPoint.setY(375);

	ball[2].BallPoint.setX(343 + 30);
	ball[2].BallPoint.setY(359);

	ball[3].BallPoint.setX(343 + 30);
	ball[3].BallPoint.setY(391);

	ball[4].BallPoint.setX(311 + 30);
	ball[4].BallPoint.setY(343);

	ball[5].BallPoint.setX(311 + 30);
	ball[5].BallPoint.setY(375);

	ball[6].BallPoint.setX(311 + 30);
	ball[6].BallPoint.setY(407);

	for (int i = 0; i <= 6; ++i) {
		ball[i].BallVector[0] = 0.;
		ball[i].BallVector[1] = 0.;
	}

	drow_dots.x = 0;
	drow_dots.y = 0;

	dots.x = 0;
	dots.y = 0;

	connect(&q_timer, SIGNAL(timeout()), SLOT(collision()));
	q_timer.start(15);
	update();
}

void Widget::paintEvent(QPaintEvent*) {
	QPainter img(this);

	img.setPen(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
	img.drawLine(250, 200, 950, 200);
	img.drawLine(950, 200, 950, 550);
	img.drawLine(950, 550, 250, 550);
	img.drawLine(250, 550, 250, 200);
	img.drawArc(QRect(220, 170, 55, 55), 270 * 16, 90 * 16);
	img.drawArc(QRect(920, 170, 55, 55), 180 * 16, 90 * 16);
	img.drawArc(QRect(920, 520, 55, 55), 90 * 16, 90 * 16);
	img.drawArc(QRect(220, 520, 55, 55), 0 * 16, 90 * 16);

	img.setBrush(Qt::white);
	img.drawEllipse(ball[0].BallPoint, 15, 15);

	for (int i = 1; i <= 6; ++i)
	{
		img.setBrush(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
		img.drawEllipse(ball[i].BallPoint, 15, 15);
	}
	if (check) {
		QPen pen = img.pen();
		pen.setStyle(Qt::DashLine);
		img.setPen(pen);
		img.drawLine(ball[0].BallPoint.x(), ball[0].BallPoint.y(), drow_dots.x, drow_dots.y);
	}
}

void Widget::mousePressEvent(QMouseEvent* event) {
	if (event->buttons() == Qt::LeftButton) {
		dots.x = event->pos().x();
		dots.y = event->pos().y();
		checking();
		if (check) {
			drow_dots.x = event->pos().x();
			drow_dots.y = event->pos().y();
		}
	}
}

void Widget::mouseMoveEvent(QMouseEvent* event) {
	checking();

	if (check && event->buttons() == Qt::LeftButton) {
		drow_dots.x = event->pos().x();
		drow_dots.y = event->pos().y();
	}
}

void Widget::mouseReleaseEvent(QMouseEvent* event) {
	event->button();
	check = false;
	ball[0].BallVector[0] = (-drow_dots.x + ball[0].BallPoint.x()) / 7;
	ball[0].BallVector[1] = (-drow_dots.y + ball[0].BallPoint.y()) / 7;

	QMediaPlayer* player1 = new QMediaPlayer(this);
	player1->setMedia(QUrl("udar-po-sharu.mp3"));
	player1->setVolume(50);
	player1->play();
}

int Widget::mod(int x, int y, int x0, int y0) {
	int mod;
	mod = sqrt(pow((x - x0), 2) + pow((y - y0), 2));
	return mod;
}

void Widget::checking() {
	int m, x, y;
	x = ball[0].BallPoint.x();
	y = ball[0].BallPoint.y();
	m = mod(dots.x, dots.y, x, y);
	if (m <= 15) {
		check = true;
	}
	else check = false;
}

void Widget::collision() {
	for (int i = 0; i <= 6; ++i) {
		if (ball[i].BallPoint.x() <= 305)
			if (ball[i].BallPoint.y() <= 255 || ball[i].BallPoint.y() >= 495)
			{
				if (i == 0)
				{
					ball[i].BallPoint.setX(825);
					ball[i].BallPoint.setY(375);
				}
				else {
					ball[i].BallPoint.setX(-100);
					ball[i].BallPoint.setY(-100);
				}
			}

		if (ball[i].BallPoint.x() >= 895)
			if (ball[i].BallPoint.y() <= 255 || ball[i].BallPoint.y() >= 495)
			{
				if (i == 0)
				{
					ball[i].BallPoint.setX(825);
					ball[i].BallPoint.setY(375);
				}
				else {
					ball[i].BallPoint.setX(-100);
					ball[i].BallPoint.setY(-100);
				}
			}

		ball[i].BallVector[0] = ball[i].BallVector[0] * 0.98;
		ball[i].BallVector[1] = ball[i].BallVector[1] * 0.98;

		if (((ball[i].BallVector[0] <= 1.3) && (ball[i].BallVector[0] >= 0)) || ((ball[i].BallVector[0] >= -1.3) && (ball[i].BallVector[0] <= 0)))
			ball[i].BallVector[0] = 0;
		if (((ball[i].BallVector[1] <= 1.3) && (ball[i].BallVector[1] >= 0)) || ((ball[i].BallVector[1] >= -1.3) && (ball[i].BallVector[1] <= 0)))
			ball[i].BallVector[1] = 0;

		double x_ball, y_ball;
		x_ball = ball[i].BallPoint.x() + ball[i].BallVector[0];
		y_ball = ball[i].BallPoint.y() + ball[i].BallVector[1];

		ball[i].BallPoint.setX(x_ball);
		ball[i].BallPoint.setY(y_ball);

		if (ball[i].BallPoint.x() <= 265 && ball[i].BallPoint.x() >=0)
			if (ball[i].BallVector[0] < 0)
			{
				ball[i].BallVector[0] = -ball[i].BallVector[0];

				QMediaPlayer* player1 = new QMediaPlayer(this);
				player1->setMedia(QUrl("bort.mp3"));
				player1->setVolume(50);
				player1->play();
			}

		if (ball[i].BallPoint.y() <= 215 && ball[i].BallPoint.y() >= 0)
			if (ball[i].BallVector[1] < 0)
			{
				ball[0].BallVector[1] = -ball[i].BallVector[1];

				QMediaPlayer* player1 = new QMediaPlayer(this);
				player1->setMedia(QUrl("bort.mp3"));
				player1->setVolume(50);
				player1->play();
			}

		if (ball[i].BallPoint.x() >= 935)
			if (ball[i].BallVector[0] > 0)
			{
				ball[i].BallVector[0] = -ball[i].BallVector[0];

				QMediaPlayer* player1 = new QMediaPlayer(this);
				player1->setMedia(QUrl("bort.mp3"));
				player1->setVolume(50);
				player1->play();
			}

		if (ball[i].BallPoint.y() >= 535)
			if (ball[i].BallVector[1] > 0)
			{
				ball[i].BallVector[1] = -ball[i].BallVector[1];

				QMediaPlayer* player1 = new QMediaPlayer(this);
				player1->setMedia(QUrl("bort.mp3"));
				player1->setVolume(50);
				player1->play();
			}

		for (int n = i + 1; n < 15; ++n) {
			int m = mod(ball[i].BallPoint.x(), ball[i].BallPoint.y(), ball[n].BallPoint.x(), ball[n].BallPoint.y());
			if (m <= 30) {
				double bi0, bi1, bn0, bn1;
				bi0 = ball[i].BallVector[0];
				bi1 = ball[i].BallVector[1];
				bn0 = ball[n].BallVector[0];
				bn1 = ball[n].BallVector[1];
				ball[i].BallVector[0] = -bi0 / 2 + bn0 / 2;
				ball[i].BallVector[1] = -bi1 / 2 + bn1 / 2;
				ball[n].BallVector[0] = -bn0 / 2 + bi0;
				ball[n].BallVector[1] = -bn1 / 2 + bi1;
			}
		}
		if ((mod(x_ball, y_ball, 265, 215) <= 30) || (mod(x_ball, y_ball, 935, 215) <= 30) || (mod(x_ball, y_ball, 265, 535) <= 30) || (mod(x_ball, y_ball, 935, 535) <= 30)) {
			std::cout << "GG";
		}
	}
	update();
}