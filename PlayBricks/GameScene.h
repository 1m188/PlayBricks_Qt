#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QPixmap"
#include "QLabel"
#include "QTimer"

//��Ϸ������
class GameScene : public Scene
{
	Q_OBJECT

private:
	//һϵ����ԴͼƬ
	QPixmap ballPixmap;
	QPixmap paddlePixmap;
	QPixmap block_bluePixmap;
	QPixmap block_greenPixmap;
	QPixmap block_redPixmap;

	QLabel *ballLabel; //��
	QLabel *paddleLabel; //����
	QVector<QVector<QLabel *>> blockLabelVector; //ש���ά����

	//�����ƶ���ʱ��
	QTimer paddleMoveLeftTimer; //��
	QTimer paddleMoveRightTimer; //��
	QTimer ballMoveTimer; //���ƶ���ʱ��

	int ballMoveDx; //��ÿ����x�����ƶ��ľ���
	int ballMoveDy; //��ÿ����y�����ƶ��ľ���

	bool isCrash(QLabel *l1, QLabel *l2); //�Ƿ���ײ

public:
	GameScene(Window *parent);
	~GameScene();

	void init() override;

protected:
	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //...�ͷŰ���...

	private slots:
	void paddleMoveLeftSlot(); //���������ƶ��źŲ�
	void paddleMoveRightSlot(); //...��...
	void ballMoveSlot(); //���ƶ�
};

#endif // GAMESCENE_H
