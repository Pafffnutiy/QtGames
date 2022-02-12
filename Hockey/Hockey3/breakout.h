#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QWidget>
#include <QMenuBar>
#include <QKeyEvent>
#include "ball.h"
//#include "brick.h"
#include "paddle1.h"
#include "paddle2.h"

class Breakout : public QWidget {
public:
	QMenuBar* mainMenu;
	Breakout(QWidget* parent = 0);

	~Breakout();
	int flag = 1;

protected:
	void paintEvent(QPaintEvent*);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent*);
	void keyReleaseEvent(QKeyEvent*);
	void drawObjects(QPainter*);
	void finishGame(QPainter*, QString);
	void moveObjects();

	void startGame();
	void pauseGame();
	void stopGame();
	void victory();
	void checkCollision();

private:
	int a = 0, b = 0;
	int x;
	int timerId;
	static const int N_OF_BRICKS = 40;
	static const int N_OF_BRICKS1 = 56;
	static const int DELAY = 4;
	static const int BOTTOM_EDGE = 385;
	Ball* ball;
	paddle1* padle1;
	paddle2* padle2;
	//Brick* bricks[N_OF_BRICKS];
	//Brick* bricks1[N_OF_BRICKS1];
	bool gameOver;
	bool gameWon;
	bool gameStarted;
	bool paused;
};
#endif // BREAKOUT_H
