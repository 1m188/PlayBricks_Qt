#include "Window.h"
#include "Director.h"
#include "GameScene.h"
#include "QApplication"
#include "QDeskTopWidget"

Window::Window()
	: QWidget(Q_NULLPTR)
{
	//�����������
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, true);

	//����ʹ�С
	setWindowTitle(tr(u8"��ש��"));
	setFixedSize(1000, 800);

	//�ƶ�����Ļ����
	QRect rect = frameGeometry();
	rect.moveCenter(QApplication::desktop()->availableGeometry().center());
	move(rect.topLeft());
}

Window::~Window()
{

}

void Window::keyPressEvent(QKeyEvent * event)
{
	Director::getInstance()->getNowScene()->keyPressEvent(event);
}

void Window::keyReleaseEvent(QKeyEvent * event)
{
	Director::getInstance()->getNowScene()->keyReleaseEvent(event);
}

void Window::show()
{
	GameScene *gameScene = new GameScene(this);
	Director::getInstance()->setNowScene(gameScene);
	gameScene->init();
	gameScene->show();
	QWidget::show();
}