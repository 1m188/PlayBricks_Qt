#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "CalculateStatusThread.h"

//��Ϸ������
class GameScene : public Scene
{
	Q_OBJECT

private:
	//һϵ����ԴͼƬ
	QPixmap ballPixmap; //���ͼƬ
	QPixmap paddlePixmap; //����ͼƬ
	QVector<QPixmap> bricksImageVector; //ש��ͼƬ����������ɫ�����������飩

	int difficulty; //�Ѷ�ϵ��
	int nowScore; //��ǰ�÷�

public:
	GameScene(Window *parent);
	~GameScene();

	void init(int difficulty); //���ػ���ͬ����������ʼ���������Ѷȣ�Ŀǰ��0��1��2������λ

	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //��д�ͷŰ����¼�

protected:
	void paintEvent(QPaintEvent *event) override; //��д�����¼�
};

#endif // GAMESCENE_H
