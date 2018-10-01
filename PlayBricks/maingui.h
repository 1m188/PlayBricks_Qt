#ifndef MAINGUI_H
#define MAINGUI_H

#include <QWidget>
#include "QPixmap"
#include "QLabel"

#ifdef _DEBUG
#include "QDebug"
#endif // _DEBUG


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

	//һЩ��ϷԪ�صı�ǩ
	QLabel *ballLabel;
	QLabel *paddleLabel;
	QVector<QVector<QLabel *>> blockLabelVector; //ש���ά����

	bool isStart; //��Ϸ�Ƿ�ʼ

protected:
	void keyPressEvent(QKeyEvent *event) override; //��д�����¼�
};

#endif // MAINGUI_H
