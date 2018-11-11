#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Window.h"

//������
class Director
{
private:
	Director(); //��ֹ��ʾ����ʵ��

	static Director *instance; //����ģʽ��Ψһ��ָ��

	Window *window; //��Ϸ����ָ��ʵ��

public:
	Director(const Director &) = delete;
	Director &operator=(const Director &) = delete;
	~Director();

	static Director *getInstance(); //��õ���ָ��

	void setWindow(Window *window); //������Ϸ����ʵ��
	Window *getWindow(); //��ȡ��Ϸ����ʵ��
};

#endif // !DIRECTOR_H
