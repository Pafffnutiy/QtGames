#include "breakout.h"
#include <QPainter>
#include <QString>
#include <QLabel>
#include <QApplication>
#include <QtMultimedia\qmediaplayer.h> 
Breakout::Breakout(QWidget* parent) : QWidget(parent)
{
	x = 0;
	gameOver = false;
	gameWon = false;
	paused = false;
	gameStarted = false;
	ball = new Ball();
	padle1 = new paddle1();
	padle2 = new paddle2();
}
void Breakout::paintEvent(QPaintEvent*) {
	QPainter painter(this);

	if (gameOver) {
		finishGame(&painter, "RIGHT PLAYER WINS");
	}
	else if (gameWon) {
		finishGame(&painter, "LEFT PLAYER WINS");
	}
	else {
		drawObjects(&painter);
	}
}
void Breakout::drawObjects(QPainter* painter) {
	QPen p;
	p.setColor(Qt::red);
	p.setWidth(2);
	QRect r(0, 0, 600, 400);
	painter->fillRect(r, QColor(214, 255, 250));

	painter->drawRect(r);
	painter->drawText(600, 10, "  Left");
	painter->drawText(630, 10, "      Right");

	painter->drawText(615, 30, QString::number(a));
	painter->drawText(660, 30, QString::number(b));

	painter->setPen(p);
	
	painter->drawLine(300, 0, 300, 400);
	painter->drawLine(115, 40, 115, 90);
	painter->drawLine(475, 40, 475, 90);
	painter->drawLine(475, 320, 475, 370);
	painter->drawLine(115, 320, 115, 370);

	painter->drawEllipse(225, 125, 150, 150);
	painter->drawEllipse(90, 40, 50, 50);
	painter->drawEllipse(90, 320, 50, 50);
	painter->drawEllipse(450, 40, 50, 50);
	painter->drawEllipse(450, 320, 50, 50);
	p.setColor(Qt::black);
	p.setWidth(7);
	painter->setPen(p);
	painter->drawLine(2, 100, 2, 300);
	painter->drawLine(600, 100, 600, 300);

	p.setColor(Qt::blue);
	p.setWidth(2);
	painter->setPen(p);
	painter->drawLine(200, 0, 200, 400);
	painter->drawLine(400, 0, 400, 400);

	painter->drawImage(ball->getRect(), ball->getImage());
	painter->drawImage(padle1->getRect(), padle1->getImage());
	painter->drawImage(padle2->getRect(), padle2->getImage());
}
void Breakout::timerEvent(QTimerEvent*)
{
	if (padle2->getRect().left() < 400)
		padle2->moveX();
	if (padle2->getRect().left() > 600)
		padle2->moveX(false);

	if (padle1->getRect().left() > 200)
		padle1->moveX();
	if (padle1->getRect().left() < 0)
		padle1->moveX(false);
	if (ball->getRect().top() >= 100 && ball->getRect().top() <= 300 && ball->getRect().right() == 600) {
		gameWon = 1; victory(); a++;
	}
	if (ball->getRect().top() >= 100 && ball->getRect().top() <= 300 && ball->getRect().left() == 0) {
		gameOver = 1;
		stopGame(); b++;
	}
	moveObjects();
	checkCollision();

	repaint();
}
void Breakout::keyReleaseEvent(QKeyEvent* e) {
	int dx = 0, dy = 0;

	switch (e->key()) {
	case Qt::Key_Right:
		dx = 0;
		padle2->setDx(dx);
		break;

	case Qt::Key_Left:

		dx = 0;
		padle2->setDx(dx);

		break;
	case Qt::Key_Up:
		dy = 0;
		padle2->setDy(dy);
		break;

	case Qt::Key_Down:
		dy = 0;
		padle2->setDy(dy);
		break;
	case Qt::Key_A:
		dx = 0;
		padle1->setDx(dx);
		break;
	case Qt::Key_D:
		dx = 0;
		padle1->setDx(dx);
		break;
	case Qt::Key_W:
		dy = 0;
		padle1->setDy(dy);
		break;
	case Qt::Key_S:
		dy = 0;
		padle1->setDy(dy);
		break;
	}
}
void Breakout::keyPressEvent(QKeyEvent* e) {
	int dx = 0, dy = 0;

	switch (e->key()) {
	case Qt::Key_Right:

		dx = 1;
		padle2->setDx(dx);

		break;

	case Qt::Key_Left:

		dx = -1;
		padle2->setDx(dx);

		break;
	case Qt::Key_Up:
		dy = -1;
		padle2->setDy(dy);
		break;

	case Qt::Key_Down:
		dy = 1;
		padle2->setDy(dy);
		break;

	case Qt::Key_P:

		pauseGame();
		break;

	case Qt::Key_Space:

		startGame();
		break;

	case Qt::Key_Escape:

		qApp->exit();
		break;
	case Qt::Key_A:
		dx = -1;
		padle1->setDx(dx);
		break;
	case Qt::Key_W:
		dy = -1;
		padle1->setDy(dy);
		break;
	case Qt::Key_S:
		dy = 1;
		padle1->setDy(dy);
		break;
	case Qt::Key_D:
		dx = 1;
		padle1->setDx(dx);
		break;
	default:
		QWidget::keyPressEvent(e);
	}
}
void Breakout::startGame() {
	if (!gameStarted) {
		ball->resetState();
		padle2->resetState();
		padle1->resetState();

		gameOver = false;
		gameWon = false;
		gameStarted = true;
		timerId = startTimer(DELAY);
	}
}
void Breakout::pauseGame() {
	if (paused) {
		timerId = startTimer(DELAY);
		paused = false;
	}
	else {
		paused = true;
		killTimer(timerId);
	}
}
void Breakout::stopGame() {
	killTimer(timerId);
	gameOver = true;
	gameStarted = false;
}
void Breakout::victory() {
	killTimer(timerId);
	gameWon = true;
	gameStarted = false;
}
void Breakout::moveObjects() {
	ball->autoMove();
	padle2->move();
	padle1->move();
}
Breakout::~Breakout() {
	delete ball;
	delete padle1;
	delete padle2;
}
void Breakout::finishGame(QPainter* painter, QString message) {
	QFont font("Times New Roman", 10, QFont::Bold);
	QFontMetrics fm(font);
	int textWidth = fm.maxWidth();

	QMediaPlayer* pl = new QMediaPlayer(this);
	pl->setMedia(QUrl("Goal.mp3"));
	pl->setVolume(30);
	pl->play();

	painter->setFont(font);
	int h = height();
	int w = width();

	painter->translate(QPoint(w / 2 - 70, h / 2 - 10));
	painter->drawText(-textWidth / 2, 0, message);
}
void Breakout::checkCollision() {
	if ((ball->getRect()).intersects(padle1->getRect())) {
		int paddleLPos = padle1->getRect().left();
		int ballLPos = ball->getRect().left();

		int paddleRPos = padle1->getRect().right();
		int ballRPos = ball->getRect().right();

		int first = paddleLPos + 8;
		int second = paddleLPos + 16;
		int third = paddleLPos + 24;
		int fourth = paddleLPos + 32;

		int first1 = paddleRPos + 8;
		int second2 = paddleRPos + 16;
		int third3 = paddleRPos + 24;
		int fourth4 = paddleRPos + 32;

		if (ballLPos < first1) {
			ball->setXDir(-1);
			ball->setYDir(1);
		}
		if (ballRPos > first) {
			ball->setXDir(1);
			ball->setYDir(-1);
		}

		if (ballLPos >= first1 && ballLPos < second2) {
			ball->setXDir(1);
			ball->setYDir(1 * ball->getYDir());
		}
		if (ballRPos >= first1 && ballRPos < second2) {
			ball->setXDir(1);
			ball->setYDir(1 * ball->getYDir());
		}

		if (ballLPos >= second && ballLPos < third) {
			ball->setXDir(0);
			ball->setYDir(-1);
		}
		if (ballRPos >= second2 && ballRPos < third3) {
			ball->setXDir(0);
			ball->setYDir(1);
		}

		if (ballLPos >= third && ballLPos < fourth) {
			ball->setXDir(1);
			ball->setYDir(-1 * ball->getYDir());
		}
		if (ballRPos >= third3 && ballRPos < fourth4) {
			ball->setXDir(-1);
			ball->setYDir(1 * ball->getYDir());
		}

		if (ballLPos > fourth) {
			ball->setXDir(1);
			ball->setYDir(-1);
		}
		if (ballRPos > fourth4) {
			ball->setXDir(-1);
			ball->setYDir(1);
		}
	}
	if ((ball->getRect()).intersects(padle2->getRect())) {
		int paddleLPos = padle2->getRect().left();
		int ballLPos = ball->getRect().left();

		int paddleRPos = padle2->getRect().right();
		int ballRPos = ball->getRect().right();

		int first = paddleLPos + 8;
		int second = paddleLPos + 16;
		int third = paddleLPos + 24;
		int fourth = paddleLPos + 32;

		int first1 = paddleRPos + 8;
		int second2 = paddleRPos + 16;
		int third3 = paddleRPos + 24;
		int fourth4 = paddleRPos + 32;

		if (ballLPos > first1) {
			ball->setXDir(-1);
			ball->setYDir(1);
		}
		if (ballRPos < first) {
			ball->setXDir(-1);
			ball->setYDir(1);
		}

		if (ballLPos >= first && ballLPos < second) {
			ball->setXDir(-1);
			ball->setYDir(-1 * ball->getYDir());
		}
		if (ballRPos >= first1 && ballRPos < second2) {
			ball->setXDir(1);
			ball->setYDir(1 * ball->getYDir());
		}

		if (ballLPos >= second && ballLPos < third) {
			ball->setXDir(0);
			ball->setYDir(-1);
		}
		if (ballRPos >= second2 && ballRPos < third3) {
			ball->setXDir(0);
			ball->setYDir(1);
		}

		if (ballLPos >= third && ballLPos < fourth) {
			ball->setXDir(1);
			ball->setYDir(-1 * ball->getYDir());
		}
		if (ballRPos >= third3 && ballRPos < fourth4) {
			ball->setXDir(-1);
			ball->setYDir(1 * ball->getYDir());
		}

		if (ballLPos > fourth) {
			ball->setXDir(1);
			ball->setYDir(-1);
		}
		if (ballRPos > fourth4) {
			ball->setXDir(-1);
			ball->setYDir(1);
		}
	}
}