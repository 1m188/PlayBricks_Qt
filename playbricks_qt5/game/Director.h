#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "Scene.h"

//������
class Director
{
private:
	Director(); //��ֹ��ʾ����ʵ��

	static Director *instance; //����ģʽ��Ψһ��ָ��

	Window *window = nullptr; //��Ϸ����ָ��ʵ��
	Scene *nowScene = nullptr; //��ǰ����Ӧ����

public:
	Director(const Director &) = delete;
	Director &operator=(const Director &) = delete;
	~Director();

	static Director *getInstance(); //��õ���ָ��

	void setWindow(Window *window); //������Ϸ����ʵ��
	Window *getWindow(); //��ȡ��Ϸ����ʵ��
	void setNowScene(Scene *nowScene); //���õ�ǰ����Ӧ����
	Scene *getNowScene(); //��ȡ��ǰ����Ӧ����
};

#endif // !DIRECTOR_H
