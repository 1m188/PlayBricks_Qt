#ifndef THEMECHOOSESCENE_H
#define THEMECHOOSESCENE_H

#include "Scene.h"

//����ѡ�񳡾�
class ThemeChooseScene : public Scene
{
	Q_OBJECT

public:
	ThemeChooseScene(Window *parent);
	~ThemeChooseScene();

	void init() override; //��ʼ������

	private slots:
	void themeChooseButtonClicked(); //��������ѡ��ť
	void returnToStartSceneButtonClicked(); //�������ؿ�ʼ������ť
};

#endif // THEMECHOOSESCENE_H
