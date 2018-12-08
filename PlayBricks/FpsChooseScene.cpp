#include "FpsChooseScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QLabel"
#include "QPushButton"
#include "QSlider"
#include "QGridLayout"

FpsChooseScene::FpsChooseScene(Window *parent)
	: Scene(parent)
{

}

FpsChooseScene::~FpsChooseScene()
{

}

void FpsChooseScene::init()
{
	//�ؼ�
	QLabel *infoLabel = new QLabel(this);
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(QFont(u8"΢���ź�", 40));
	infoLabel->setText(tr(u8"֡ �� ѡ ��"));

	QLabel *fpsLabel = new QLabel(this);
	fpsLabel->setAlignment(Qt::AlignCenter);
	fpsLabel->setFont(QFont(u8"΢���ź�", 20));
	fpsLabel->setText(tr(u8"FPS"));

	QLabel *fpsValueLabel = new QLabel(this);
	fpsValueLabel->setAlignment(Qt::AlignCenter);
	fpsValueLabel->setFont(QFont(u8"΢���ź�", 20));
	fpsValueLabel->setText(QString::number(Config::getInstance()->getFps()));

	QSlider *fpsSlider = new QSlider(this);
	fpsSlider->setOrientation(Qt::Horizontal);
	fpsSlider->setMinimum(30);
	fpsSlider->setMaximum(60);
	fpsSlider->setSingleStep(1);
	fpsSlider->setValue(fpsValueLabel->text().toInt());
	//fpsֵ��ʾ��label�ϵ���ʾֵ��slider�������仯
	connect(fpsSlider, &QSlider::valueChanged, this, [=](int value) {fpsValueLabel->setText(QString::number(value)); });
	//ֱ���û��ͷ�sliderȷ��֮��Ÿ������������fpsֵ
	connect(fpsSlider, &QSlider::sliderReleased, this, [=]() {Config::getInstance()->setFps(fpsSlider->value()); });

	QPushButton *returnToStartSceneButton = new QPushButton(this);
	returnToStartSceneButton->setFont(QFont(u8"΢���ź�", 15));
	returnToStartSceneButton->setText(tr(u8"���ؿ�ʼ����"));
	connect(returnToStartSceneButton, &QPushButton::clicked, this, &FpsChooseScene::returnToStartSceneButtonClicked);

	//����
	QGridLayout *layout = new QGridLayout(this);
	layout->addWidget(infoLabel, 0, 0, 10, 15);
	layout->addWidget(fpsLabel, 10, 0, 4, 5);
	layout->addWidget(fpsSlider, 10, 5, 4, 5);
	layout->addWidget(fpsValueLabel, 10, 10, 4, 5);
	layout->addWidget(returnToStartSceneButton, 14, 5, 4, 5);
}

void FpsChooseScene::returnToStartSceneButtonClicked()
{
	StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
	Director::getInstance()->setNowScene(startScene);
	startScene->init();
	startScene->show();
	deleteLater();
}