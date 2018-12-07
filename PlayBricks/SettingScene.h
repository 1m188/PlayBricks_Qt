#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include "Scene.h"

//���ó���
class SettingScene : public Scene
{
	Q_OBJECT

public:
	SettingScene(Window *parent);
	~SettingScene();

	void init() override; //��ʼ������

	private slots:
	void themeButtonClicked(); //��������ѡ��ť
	void FpsButtonClicked(); //����֡��ѡ��ť
	void returnToStartSceneButtonClicked(); //�������ؿ�ʼ���水ť
};

#endif // SETTINGSCENE_H
