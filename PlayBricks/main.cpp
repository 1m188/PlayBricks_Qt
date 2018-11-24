#include <QtWidgets/QApplication>
#include "Director.h"
#include "Config.h"

int main(int argc, char *argv[])
{
#ifdef NDEBUG
	QApplication::addLibraryPath("./plugins"); //�����汾�ӳ�������Ŀ¼��Ѱ��������
#endif // NDEBUG

	QApplication a(argc, argv);
	Config::getInstance()->init(); //�ȼ�������
	Director::getInstance()->setWindow(new Window()); //������Ϸ����
	Director::getInstance()->getWindow()->show(); //��ʾ����
	a.exec();
	Config::getInstance()->uninit(); //�����������
	return 0;
}
