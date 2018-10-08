#include "Director.h"

Director *Director::instance = nullptr; //��ʼ������ָ��

Director::Director()
{

}

Director::~Director()
{

}

Director * Director::getInstance()
{
	//�������ָ��Ϊ�գ�����һ��
	if (!instance)
	{
		instance = new Director();
	}
	return instance;
}

bool Director::isCrash(QLabel * l1, QLabel * l2)
{
	return l1->x() >= l2->x() - l1->width() && l1->x() <= l2->x() + l2->width() && l1->y() >= l2->y() - l1->height() && l1->y() <= l2->y() + l2->height();
}