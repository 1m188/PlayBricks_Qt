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
};

#endif // SCENE_H
