#include "DifficultyChooseScene.h"
#include "Director.h"
#include "StartScene.h"
#include "GameScene.h"
#include "QLabel"
#include "QPushButton"
#include "QGridLayout"

DifficultyChooseScene::DifficultyChooseScene(Window *parent)
	: Scene(parent)
{

}

DifficultyChooseScene::~DifficultyChooseScene()
{

}

void DifficultyChooseScene::init()
{
	//�ؼ�
	QLabel *infoLabel = new QLabel(this);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(QFont(u8"΢���ź�", 40));
	infoLabel->setText(tr(u8"��  ��  ѡ  ��"));

	QPushButton *easyButton = new QPushButton(this);
	easyButton->setObjectName("0");
	easyButton->setFont(QFont(u8"΢���ź�", 15));
	easyButton->setText(tr(u8"��"));
	connect(easyButton, &QPushButton::clicked, this, &DifficultyChooseScene::difficultyChooseButtonClicked);

	QPushButton *mediumButton = new QPushButton(this);
	mediumButton->setObjectName("1");
	mediumButton->setFont(QFont(u8"΢���ź�", 15));
	mediumButton->setText(tr(u8"�е�"));
	connect(mediumButton, &QPushButton::clicked, this, &DifficultyChooseScene::difficultyChooseButtonClicked);

	QPushButton *difficultButton = new QPushButton(this);
	difficultButton->setObjectName("2");
	difficultButton->setFont(QFont(u8"΢���ź�", 15));
	difficultButton->setText(tr(u8"����"));
	connect(difficultButton, &QPushButton::clicked, this, &DifficultyChooseScene::difficultyChooseButtonClicked);

	QPushButton *returnToStartSceneButton = new QPushButton(this);
	returnToStartSceneButton->setFont(QFont(u8"΢���ź�", 15));
	returnToStartSceneButton->setText(tr(u8"���ؿ�ʼ����"));
	connect(returnToStartSceneButton, &QPushButton::clicked, this, &DifficultyChooseScene::returnToStartSceneButtonClicked);

	//����
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(infoLabel, 0, 0, 10, 15);
	layout->addWidget(easyButton, 10, 5, 2, 5);
	layout->addWidget(mediumButton, 12, 5, 2, 5);
	layout->addWidget(difficultButton, 14, 5, 2, 5);
	layout->addWidget(returnToStartSceneButton, 16, 5, 2, 5);
}

void DifficultyChooseScene::difficultyChooseButtonClicked()
{
	GameScene *gameScene = new GameScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(gameScene);
	gameScene->init(sender()->objectName().toInt()); //ͨ������Ԥ�����õ�objectname����ֱ��get���Ѷ�ϵ����������ʼ��
	gameScene->show();
	deleteLater();
}

void DifficultyChooseScene::returnToStartSceneButtonClicked()
{
	StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(startScene);
	startScene->init();
	startScene->show();
	deleteLater();
}