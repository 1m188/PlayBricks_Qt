#include "StartScene.h"
#include "Director.h"
#include "DifficultyChooseScene.h"
#include "HighestScoreScene.h"
#include "SettingScene.h"
#include "QLabel"
#include "QPushButton"
#include "QGridLayout"
#include "QApplication"

StartScene::StartScene(Window *parent)
	: Scene(parent)
{

}

StartScene::~StartScene()
{

}

void StartScene::init()
{
	//�ؼ�
	QLabel *infoLabel = new QLabel(this);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(QFont(u8"΢���ź�", 40));
	infoLabel->setText(tr(u8"��  ש  ��"));

	QPushButton *newGameButton = new QPushButton(this);
	newGameButton->setFont(QFont(u8"΢���ź�", 15));
	newGameButton->setText(tr(u8"��ʼ����Ϸ"));
	connect(newGameButton, &QPushButton::clicked, this, &StartScene::newGameButtonClicked);

	QPushButton *highestScoreButton = new QPushButton(this);
	highestScoreButton->setFont(QFont(u8"΢���ź�", 15));
	highestScoreButton->setText(tr(u8"��߷�"));
	connect(highestScoreButton, &QPushButton::clicked, this, &StartScene::highestScoreButtonClicked);

	QPushButton *settingButton = new QPushButton(this);
	settingButton->setFont(QFont(u8"΢���ź�", 15));
	settingButton->setText(tr(u8"����"));
	connect(settingButton, &QPushButton::clicked, this, &StartScene::settingButtonClicked);

	QPushButton *exitButton = new QPushButton(this);
	exitButton->setFont(QFont(u8"΢���ź�", 15));
	exitButton->setText(tr(u8"�˳�"));
	connect(exitButton, &QPushButton::clicked, QApplication::quit);

	//����
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(infoLabel, 0, 0, 10, 15);
	layout->addWidget(newGameButton, 10, 5, 2, 5);
	layout->addWidget(highestScoreButton, 12, 5, 2, 5);
	layout->addWidget(settingButton, 14, 5, 2, 5);
	layout->addWidget(exitButton, 16, 5, 2, 5);
}

void StartScene::newGameButtonClicked()
{
	DifficultyChooseScene *difficultyChooseScene = new DifficultyChooseScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(difficultyChooseScene);
	difficultyChooseScene->init();
	difficultyChooseScene->show();
	deleteLater();
}

void StartScene::highestScoreButtonClicked()
{
	HighestScoreScene *highestScoreScene = new HighestScoreScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(highestScoreScene);
	highestScoreScene->init();
	highestScoreScene->show();
	deleteLater();
}

void StartScene::settingButtonClicked()
{
	SettingScene *settingScene = new SettingScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(settingScene);
	settingScene->init();
	settingScene->show();
	deleteLater();
}