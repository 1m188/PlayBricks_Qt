#ifndef PADDLE_H
#define PADDLE_H

#include "Sprite.h"

//������
class Paddle :public Sprite
{
private:
	//ÿ�κ����ƶ���������
	int dx;

	//�Ƿ�����/���ƶ�
	bool isLefting;
	bool isRighting;

public:
	Paddle();
	Paddle(int x, int y, int width, int height, QPixmap image, int dx, bool isLefting, bool isRighting);
	~Paddle();

	//��ȡ/����ÿ�κ����ƶ���������
	const int getDx() const { return dx; }
	void setDx(int dx) { this->dx = dx; }

	//��ȡ/�����Ƿ�����/���ƶ�
	const bool getIsLefting() const { return isLefting; }
	void setIsLefting(bool isLefting) { this->isLefting = isLefting; }
	const bool getIsRighting() const { return isRighting; }
	void setIsRighting(bool isRighting) { this->isRighting = isRighting; }
};

#endif // PADDLE_H
