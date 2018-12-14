#ifndef SPRITE_H
#define SPRITE_H

#include "QPixmap"

//������
class Sprite
{
private:
	//���Ͻ�����
	int x;
	int y;

	//���
	int width;
	int height;

	//ͼƬ
	QPixmap image;

public:
	Sprite();
	Sprite(int x, int y, int width, int height, QPixmap image);
	virtual ~Sprite();

	//��ȡ/��������
	int getX() const { return x; }
	void setX(int x) { this->x = x; }
	int getY() const { return y; }
	void setY(int y) { this->y = y; }

	//��ȡ/���ÿ��
	int getWidth() const { return width; }
	void setWidth(int width) { this->width = width; }
	int getHeight() const { return height; }
	void setHeight(int height) { this->height = height; }

	//��ȡ/����ͼƬ
	QPixmap getImage() const { return image; }
	void setImage(QPixmap image) { this->image = image; }

	//��ײ���
	bool isCollided(Sprite s) const;
};

#endif // SPRITE_H
