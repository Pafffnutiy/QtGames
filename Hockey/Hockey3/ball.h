#ifndef BALL_H
#define BALL_H
#include <QImage>
#include <QRect>

class Ball
{
public:
	Ball();
	~Ball();

public:
	void resetState();
	void autoMove();
	void setXDir(int);
	void setYDir(int);
	int getXDir();
	int getYDir();
	QRect getRect();
	QImage& getImage();

private:
	int xdir;
	int ydir;
	QImage image;
	QRect rect;
	static const int INITIAL_X = 70;
	static const int INITIAL_Y = 182;
	static const int RIGHT_EDGE = 600;
};

#endif // BALL_H
