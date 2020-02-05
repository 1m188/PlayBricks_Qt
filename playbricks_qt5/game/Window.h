#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

//��Ϸ������
class Window : public QWidget
{
	Q_OBJECT

public:
	Window();
	~Window();

	void show(); //��дshow�������Է���һ����ʼ����

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // WINDOW_H
