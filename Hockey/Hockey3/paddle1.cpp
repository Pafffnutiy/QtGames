#include "paddle1.h"

#include <iostream>

paddle1::paddle1() {
	dx = 0; dy = 0;

	image.load("paddle.jpg");

	rect = image.rect();
	resetState();
}

paddle1::~paddle1() {
	//std::cout << ("Paddle deleted") << std::endl;
}

void paddle1::setDx(int x) {
	dx = x;
}
void paddle1::setDy(int y) {
	dy = y;
}

void paddle1::move() {
	int x = rect.x() + dx;
	int y = rect.y() + dy;

	rect.moveTo(x, y);
}

void paddle1::resetState() {
	rect.moveTo(60, 172);
}

QRect paddle1::getRect() {
	return rect;
}

QImage& paddle1::getImage() {
	return image;
}
void paddle1::moveX(bool flag) {
	if (flag)
		rect.moveTo(200, rect.y());
	else
		rect.moveTo(0, rect.y());
}