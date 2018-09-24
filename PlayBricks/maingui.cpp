#include "maingui.h"
#include "QApplication"
#include "QDeskTopWidget"
#include "gamescene.h"

MainGui::MainGui(QWidget *parent)
	: QWidget(parent)
{
	//�����������
	setAttribute(Qt::WA_DeleteOnClose, true);
	setAttribute(Qt::WA_QuitOnClose, true);

	//����ʹ�С
	setWindowTitle(tr("QtGame"));
	setFixedSize(1000, 800);

	//�ƶ�����Ļ����
	QRect rect = frameGeometry();
	rect.moveCenter(QApplication::desktop()->availableGeometry().center());
	move(rect.topLeft());

	GameScene *gameScene = new GameScene(this);
	gameScene->setFixedSize(size());
}

MainGui::~MainGui()
{

}
