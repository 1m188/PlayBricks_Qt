#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "QLabel"

//������
class Director
{
private:
	Director(); //��ֹ��ʾ����ʵ��
	static Director *instance; //����ģʽ��Ψһ��ָ��

public:
	~Director();
	static Director *getInstance(); //��õ���ָ��

	bool isCrash(QLabel *l1, QLabel *l2); //�Ƿ���ײ
};

#endif // !DIRECTOR_H
