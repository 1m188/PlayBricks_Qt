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
	QPixmap ballPixmap; //���ͼƬ
	QPixmap paddlePixmap; //����ͼƬ
	QVector<QPixmap> blockPixmapVector; //ש��ͼƬ����������ɫ�����������飩

	QLabel *ballLabel; //��
	QLabel *paddleLabel; //����
	QVector<QVector<QLabel *>> blockLabelVector; //ש���ά����

	QLabel *scoreLabel; //�÷���ʾ
	unsigned int nowScore; //��ǰ�÷�

	unsigned int difficulty; //�Ѷ�ϵ��

	QTimer paddleMoveLeftTimer; //�������ƶ���ʱ��
	QTimer paddleMoveRightTimer; //�������ƶ���ʱ��
	QTimer ballMoveTimer; //���ƶ���ʱ��

	QPair<int, int> ballMoveDxy; //��ÿ����x�����y�����ƶ��ľ���
	int paddleMoveDx; //�����ں�����ÿ���ƶ��ľ���

	void paddleMove(int distance); //�����ƶ�
	bool isCrash(QLabel *l1, QLabel *l2); //�Ƿ���ײ

public:
	GameScene(Window *parent);
	~GameScene();

	void init(int difficulty); //���ػ���ͬ����������ʼ���������Ѷȣ�Ŀǰ��0��1��2������λ

protected:
	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //��д�ͷŰ����¼�

	private slots:
	void ballMoveSlot(); //���ƶ��źŲ�
};

#endif // GAMESCENE_H
