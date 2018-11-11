#ifndef MAINGUI_H
#define MAINGUI_H

#include <QWidget>
#include "QPixmap"
#include "QLabel"
#include "QTimer"

//��Ϸ������
class MainGui : public QWidget
{
	Q_OBJECT

public:
	MainGui(QWidget *parent);
	~MainGui();

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

protected:
	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
	void keyReleaseEvent(QKeyEvent *event) override; //...�ͷŰ���...

	private slots:
	void paddleMoveLeftSlot(); //���������ƶ��źŲ�
	void paddleMoveRightSlot(); //...��...
	void ballMoveSlot(); //���ƶ�
};

#endif // MAINGUI_H
