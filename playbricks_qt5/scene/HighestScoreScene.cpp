#include "HighestScoreScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QLabel"
#include "QPushButton"
#include "QGridLayout"

HighestScoreScene::HighestScoreScene(Window *parent)
	: Scene(parent)
{

}

HighestScoreScene::~HighestScoreScene()
{

}

void HighestScoreScene::init()
{
	//�ؼ�
	QLabel *infoLabel = new QLabel(this);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(QFont(u8"΢���ź�", 40));
	infoLabel->setText(tr(u8"��  ��  ��"));

	QLabel *highestScoreLabel = new QLabel(this);
	highestScoreLabel->setAlignment(Qt::AlignCenter);
	highestScoreLabel->setFont(QFont(u8"΢���ź�", 25));
	highestScoreLabel->setText(QString::number(Config::getInstance()->getHighestScore()) + tr(u8"��") + "     " + Config::getInstance()->getHighestScorePlayer());

	QPushButton *returnToStartSceneButton = new QPushButton(this);
	returnToStartSceneButton->setFont(QFont(u8"΢���ź�", 15));
	returnToStartSceneButton->setText(tr(u8"���ؿ�ʼ����"));
	connect(returnToStartSceneButton, &QPushButton::clicked, this, &HighestScoreScene::returnToStartSceneButtonClicked);

	//����
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(infoLabel, 0, 0, 10, 15);
	layout->addWidget(highestScoreLabel, 10, 5, 3, 5);
	layout->addWidget(returnToStartSceneButton, 13, 5, 3, 5);
}

void HighestScoreScene::returnToStartSceneButtonClicked()
{
	StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(startScene);
	startScene->init();
	startScene->show();
	deleteLater();
}