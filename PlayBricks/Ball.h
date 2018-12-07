#ifndef BALL_H
#define BALL_H

#include "Sprite.h"

//����
class Ball :public Sprite
{
private:
	//ÿ���ƶ���x��y�����ϵľ���
	int dx;
	int dy;

	//�Ƿ����ƶ�
	bool isMoving;

public:
	Ball();
	Ball(int x, int y, int width, int height, QPixmap image, int dx, int dy, bool isMoving);
	~Ball();

	//��ȡ/����ÿ���ƶ���x��y�����ϵľ���
	const int getDx() const { return dx; }
	void setDx(int dx) { this->dx = dx; }
	const int getDy() { return dy; }
	void setDy(int dy) { this->dy = dy; }

	//��ȡ/�����Ƿ����ƶ�
	const int getIsMoving() const { return isMoving; }
	void setIsMoving(bool isMoving) { this->isMoving = isMoving; }
};

#endif // BALL_H
