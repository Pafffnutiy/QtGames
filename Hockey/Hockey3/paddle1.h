#ifndef PADDLE1_H
#define PADDLE1_H
#include <QImage>
#include <QRect>

class paddle1
{
public:
	paddle1();
	~paddle1();

public:
	void resetState();
	void move();
	void moveX(bool flag = true);
	void setDx(int);
	void setDy(int);
	QRect getRect();
	QImage& getImage();

private:
	QImage image;
	QRect rect;
	int dx;
	int dy;
	static const int INITIAL_X = 320;
	static const int INITIAL_Y = 180;
};

#endif // PADDLE1_H
