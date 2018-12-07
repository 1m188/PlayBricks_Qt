#include "GameScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QKeyEvent"
#include "QMessageBox"
#include "QInputDialog"
#include "QPainter"
#include "GameSprite.h"

GameScene::GameScene(Window *parent)
	: Scene(parent)
{

}

GameScene::~GameScene()
{

}

void GameScene::init(int difficulty)
{
	//��ϷԪ�س�ʼ��
	//ͼƬ��ʼ��
	ballPixmap.load(":/game/Resources/game/ball.png");
	paddlePixmap.load(":/game/Resources/game/paddle.png");
	bricksImageVector.resize(3);
	bricksImageVector[0].load(":/game/Resources/game/block_green.png");
	bricksImageVector[1].load(":/game/Resources/game/block_blue.png");
	bricksImageVector[2].load(":/game/Resources/game/block_red.png");

	//��ʼ���Ѷ�ϵ��
	this->difficulty = difficulty % 3; //��ֹ������Ѷ�ϵ��������Χ

	//�����ʼ��
	paddle = Paddle(width() / 2 - paddlePixmap.width() / 2, height() - paddlePixmap.height() - 10, paddlePixmap.width(), paddlePixmap.height(), paddlePixmap, 6 - this->difficulty, false, false);

	//���ʼ��
	ball = Ball(paddle.getX() + paddle.getWidth() / 2 - ballPixmap.width() / 2, paddle.getY() - ballPixmap.height() - 10, ballPixmap.width(), ballPixmap.height(), ballPixmap, this->difficulty * 2 + 5, this->difficulty * 2 + 5, false);

	//�÷ֳ�ʼ��
	nowScore = 0;

	//ש���ʼ��
	for (int i = 0; i < (this->difficulty) * 4 + 10; i++)
	{
		bricksVector.append(QVector<Brick>{});
		for (int j = 0; j < 16; j++)
		{
			Brick brick(j*bricksImageVector.at(this->difficulty).width(), i*bricksImageVector.at(this->difficulty).height(), bricksImageVector.at(this->difficulty).width(), bricksImageVector.at(this->difficulty).height(), bricksImageVector.at(this->difficulty), false);
			bricksVector[bricksVector.size() - 1].append(brick);
		}
	}
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat())
	{
		//���������ƶ�
		if (event->key() == Qt::Key_Left)
		{
			paddle.setIsLefting(true);
		}
		//���������ƶ�
		else if (event->key() == Qt::Key_Right)
		{
			paddle.setIsRighting(true);
		}
		//��ס�ո�������
		else if (event->key() == Qt::Key_Space)
		{
			ball.setDx(ball.getDx() * 3);
			ball.setDy(ball.getDy() * 3);
		}
		//�����û���ƶ��Ļ��������������ʼ�ƶ�
		if (!ball.getIsMoving())
		{
			ball.setIsMoving(true);
		}
	}
}

void GameScene::keyReleaseEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat())
	{
		//����ֹͣ�����ƶ�
		if (event->key() == Qt::Key_Left)
		{
			paddle.setIsLefting(false);
		}
		//����ֹͣ�����ƶ�
		else if (event->key() == Qt::Key_Right)
		{
			paddle.setIsRighting(false);
		}
		//�ͷſո������ص�ԭ�����ٶ�
		else if (event->key() == Qt::Key_Space)
		{
			ball.setDx(ball.getDx() / 3);
			ball.setDy(ball.getDy() / 3);
		}
	}
}

void GameScene::paintEvent(QPaintEvent * event)
{
	//����
	QPainter *painter = new QPainter(this);

	//���Ƶ���
	painter->drawPixmap(paddle.getX(), paddle.getY(), paddle.getImage());

	//������
	painter->drawPixmap(ball.getX(), ball.getY(), ball.getImage());

	//����ש��
	for (auto &vector : bricksVector)
	{
		for (Brick &brick : vector)
		{
			if (!brick.getIsCollided())
			{
				painter->drawPixmap(brick.getX(), brick.getY(), brick.getImage());
			}
		}
	}

	painter->end();

	Scene::paintEvent(event);
}