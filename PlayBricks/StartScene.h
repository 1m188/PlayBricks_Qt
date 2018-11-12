#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "Scene.h"

//��ʼ����
class StartScene : public Scene
{
	Q_OBJECT

public:
	StartScene(Window *parent);
	~StartScene();

	void init() override;

	private slots:
	void newGameButtonClicked(); //������ʼ����Ϸ��ť
};

#endif // STARTSCENE_H
