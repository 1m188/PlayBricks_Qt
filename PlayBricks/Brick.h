#ifndef BRICK_H
#define BRICK_H

#include "Sprite.h"

//����ש����
class Brick :Sprite
{
private:
	//�Ƿ�ײ��
	bool isCollided;

public:
	Brick();
	Brick(int x, int y, int width, int height, QPixmap image, bool isCollided);
	~Brick();

	//��ȡ/�����Ƿ�ײ��
	const bool getIsCollided() const { return isCollided; }
	void setIsCollided(bool isCollided) { this->isCollided = isCollided; }
};

#endif // BRICK_H
