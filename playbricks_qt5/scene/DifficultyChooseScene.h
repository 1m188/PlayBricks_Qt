#ifndef DIFFICULTYCHOOSESCENE_H
#define DIFFICULTYCHOOSESCENE_H

#include "Scene.h"

//�Ѷ�ѡ�񳡾�
class DifficultyChooseScene : public Scene
{
	Q_OBJECT

public:
	DifficultyChooseScene(Window *parent);
	~DifficultyChooseScene();

	void init() override; //��ʼ������

	private slots:
	void difficultyChooseButtonClicked(); //�����Ѷ�ѡ��ť
	void returnToStartSceneButtonClicked(); //�������ؿ�ʼ������ť
};

#endif // DIFFICULTYCHOOSESCENE_H
