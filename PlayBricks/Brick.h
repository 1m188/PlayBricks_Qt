#ifndef BRICK_H
#define BRICK_H

#include "Sprite.h"

//ש����
class Brick :public Sprite
{
private:
	//�Ƿ�ײ�Ϲ�
	bool isCollided;

public:
	Brick();
	Brick(int x, int y, int width, int height, QPixmap image, bool isCollided);
	~Brick();

	//��ȡ/�����Ƿ�ײ�Ϲ�
	const bool getIsCollided() const { return isCollided; }
	void setIsCollided(bool isCollided) { this->isCollided = isCollided; }
};

#endif // BRICK_H
