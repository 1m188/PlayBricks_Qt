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
	QVector<QPixmap> blockPixmapVector;

	QLabel *ballLabel; //��
	QLabel *paddleLabel; //����
	QVector<QVector<QLabel *>> blockLabelVector; //ש���ά����

	int difficulty; //�Ѷ�

	//�����ƶ���ʱ��
	QTimer paddleMoveLeftTimer; //��
	QTimer paddleMoveRightTimer; //��
	QTimer ballMoveTimer; //���ƶ���ʱ��

	int ballMoveDx; //��ÿ����x�����ƶ��ľ���
	int ballMoveDy; //��ÿ����y�����ƶ��ľ���
	int paddleMoveDx; //�����ں�����ÿ���ƶ��ľ���

	bool isCrash(QLabel *l1, QLabel *l2); //�Ƿ���ײ

public:
	GameScene(Window *parent);
	~GameScene();

	void init(int difficulty); //��ʼ���������Ѷȣ�Ŀǰ��0��1��2������λ

protected:
	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //...�ͷŰ���...

	private slots:
	void paddleMoveLeftSlot(); //���������ƶ��źŲ�
	void paddleMoveRightSlot(); //...��...
	void ballMoveSlot(); //���ƶ�
};

#endif // GAMESCENE_H
