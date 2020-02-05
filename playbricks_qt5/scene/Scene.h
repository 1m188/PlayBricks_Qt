#ifndef SCENE_H
#define SCENE_H

#include "Window.h"

//������
class Scene : public QWidget
{
	Q_OBJECT

public:
	Scene(Window *parent);
	virtual ~Scene();

	virtual void init(); //��ʼ������

	//��������Ӧ��д��public�з��������ڵ�����Щ��������Ӧ�ڴ��ڵİ������ݵ�����֮��
	virtual void keyPressEvent(QKeyEvent *event) override;
	virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
