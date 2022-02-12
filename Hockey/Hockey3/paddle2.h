#ifndef PADDLE2_H
#define PADDLE2_H
#include <QImage>
#include <QRect>

class paddle2
{
public:
	paddle2();
	~paddle2();

public:
	void resetState();
	void move();
	void setDx(int);
	void setDy(int);
	QRect getRect();
	QImage& getImage();
	QRect rect;
	void moveX(bool flag = true);

private:
	QImage image;

	int dx, dy;
	static const int INITIAL_X = 320;
	static const int INITIAL_Y = 180;
};

#endif // PADDLE2_H
