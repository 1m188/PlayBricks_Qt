#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "QTimer"

//��Ϸ������
class GameScene : public Scene
{
	Q_OBJECT

private:
	//һϵ����ԴͼƬ
	QPixmap ballPixmap; //���ͼƬ
	QPixmap paddlePixmap; //����ͼƬ
	QVector<QPixmap> bricksImageVector; //ש��ͼƬ����������ɫ�����������飩

	Paddle paddle; //����
	Ball ball; //��
	QVector<QVector<Brick>> bricksVector; //ש���ά����

	QTimer *timer; //ÿ��һ��ʱ����м��㡢���ƵĶ�ʱ��

	int difficulty; //�Ѷ�ϵ��
	int nowScore; //��ǰ�÷�

	bool isCrash(Sprite s1, Sprite s2) const; //�Ƿ���ײ
	void updateBallDxy(Sprite s); //ͨ��ԭ����ÿ���ƶ������������ײ�����������������һ���ƶ�����

public:
	GameScene(Window *parent);
	~GameScene();

	void init(int difficulty); //���ػ���ͬ����������ʼ���������Ѷȣ�Ŀǰ��0��1��2������λ

	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //��д�ͷŰ����¼�

protected:
	void paintEvent(QPaintEvent *event) override;

	private slots:
	void gameCycle(); //��Ϸѭ��
};

#endif // GAMESCENE_H
