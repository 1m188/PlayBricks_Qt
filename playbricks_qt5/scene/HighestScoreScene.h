#ifndef HIGHESTSCORESCENE_H
#define HIGHESTSCORESCENE_H

#include "Scene.h"

//��߷ֳ���
class HighestScoreScene : public Scene
{
	Q_OBJECT

public:
	HighestScoreScene(Window *parent);
	~HighestScoreScene();

	void init() override; //��ʼ������

	private slots:
	void returnToStartSceneButtonClicked(); //�������ؿ�ʼ���水ť
};

#endif // HIGHESTSCORESCENE_H
