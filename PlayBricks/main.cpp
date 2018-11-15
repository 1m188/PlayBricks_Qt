#include <QtWidgets/QApplication>
#include "Director.h"

int main(int argc, char *argv[])
{
#ifdef NDEBUG
	QApplication::addLibraryPath("./plugins"); //�����汾�ӳ�������Ŀ¼��Ѱ��������
#endif // NDEBUG

	QApplication a(argc, argv);
	Director::getInstance()->setWindow(new Window());
	Director::getInstance()->getWindow()->show();
	return a.exec();
}
