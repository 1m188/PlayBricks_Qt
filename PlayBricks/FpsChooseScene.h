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

	private slots:
	void returnToStartSceneButtonClicked(); //�������ؿ�ʼ������ť
};

#endif // FPSCHOOSESCENE_H
