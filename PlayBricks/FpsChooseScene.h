#ifndef FPSCHOOSESCENE_H
#define FPSCHOOSESCENE_H

#include "Scene.h"

//fpsѡ�񳡾�
class FpsChooseScene : public Scene
{
	Q_OBJECT

public:
	FpsChooseScene(Window *parent);
	~FpsChooseScene();

	void init() override; //��ʼ������
};

#endif // FPSCHOOSESCENE_H
