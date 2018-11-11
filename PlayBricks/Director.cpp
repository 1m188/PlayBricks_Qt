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

void Director::setWindow(Window * window)
{
	this->window = window;
}

Window * Director::getWindow()
{
	return window;
}