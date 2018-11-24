#include "ThemeChooseScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QLabel"
#include "QPushButton"
#include "QGridLayout"
#include "QFile"
#include "QApplication"

ThemeChooseScene::ThemeChooseScene(Window *parent)
	: Scene(parent)
{

}

ThemeChooseScene::~ThemeChooseScene()
{

}

void ThemeChooseScene::init()
{
	//�ؼ�
	QLabel *infoLabel = new QLabel(this);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(QFont(u8"΢���ź�", 40));
	infoLabel->setText(tr(u8"�� �� ѡ ��"));

	QPushButton *defaultButton = new QPushButton(this);
	defaultButton->setObjectName("default");
	defaultButton->setFont(QFont(u8"΢���ź�", 15));
	defaultButton->setText(tr(u8"Ĭ��"));
	connect(defaultButton, &QPushButton::clicked, this, &ThemeChooseScene::themeChooseButtonClicked);

	QPushButton *blackButton = new QPushButton(this);
	blackButton->setObjectName("black");
	blackButton->setFont(QFont(u8"΢���ź�", 15));
	blackButton->setText(tr(u8"���ź�"));
	connect(blackButton, &QPushButton::clicked, this, &ThemeChooseScene::themeChooseButtonClicked);

	QPushButton *grayButton = new QPushButton(this);
	grayButton->setObjectName("gray");
	grayButton->setFont(QFont(u8"΢���ź�", 15));
	grayButton->setText(tr(u8"������"));
	connect(grayButton, &QPushButton::clicked, this, &ThemeChooseScene::themeChooseButtonClicked);

	QPushButton *yellowButton = new QPushButton(this);
	yellowButton->setObjectName("yellow");
	yellowButton->setFont(QFont(u8"΢���ź�", 15));
	yellowButton->setText(tr(u8"ů�Ļ�"));
	connect(yellowButton, &QPushButton::clicked, this, &ThemeChooseScene::themeChooseButtonClicked);

	QPushButton *returnToStartSceneButton = new QPushButton(this);
	returnToStartSceneButton->setFont(QFont(u8"΢���ź�", 15));
	returnToStartSceneButton->setText(tr(u8"���ؿ�ʼ����"));
	connect(returnToStartSceneButton, &QPushButton::clicked, this, &ThemeChooseScene::returnToStartSceneButtonClicked);

	//����
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(infoLabel, 0, 0, 10, 15);
	layout->addWidget(defaultButton, 10, 5, 2, 5);
	layout->addWidget(blackButton, 12, 5, 2, 5);
	layout->addWidget(grayButton, 14, 5, 2, 5);
	layout->addWidget(yellowButton, 16, 5, 2, 5);
	layout->addWidget(returnToStartSceneButton, 18, 5, 2, 5);
}

void ThemeChooseScene::themeChooseButtonClicked()
{
	QString themeResourceUrl = QString(":/theme/Resources/theme/%1.qss").arg(sender()->objectName());
	Config::getInstance()->setThemeResourceUrl(themeResourceUrl);
	QFile f(themeResourceUrl);
	f.open(QIODevice::ReadOnly);
	qApp->setStyleSheet(f.readAll());
	f.close();
}

void ThemeChooseScene::returnToStartSceneButtonClicked()
{
	StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(startScene);
	startScene->init();
	startScene->show();
	deleteLater();
}