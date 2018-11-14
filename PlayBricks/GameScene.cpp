#include "GameScene.h"
#include "Director.h"
#include "StartScene.h"
#include "QApplication"
#include "QDeskTopWidget"
#include "QKeyEvent"
#include "QMessageBox"

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
	ballPixmap.load(":/PlayBricks/Resources/ball.png");
	paddlePixmap.load(":/PlayBricks/Resources/paddle.png");
	blockPixmapVector.resize(3);
	blockPixmapVector[0].load(":/PlayBricks/Resources/block_green.png");
	blockPixmapVector[1].load(":/PlayBricks/Resources/block_blue.png");
	blockPixmapVector[2].load(":/PlayBricks/Resources/block_red.png");

	//�����ʼ��
	paddleLabel = new QLabel(this);
	paddleLabel->setPixmap(paddlePixmap);
	paddleLabel->setFixedSize(paddlePixmap.size());
	paddleLabel->move(width() / 2 - paddleLabel->width() / 2, height() - paddleLabel->height() - 10);

	//���ʼ��
	ballLabel = new QLabel(this);
	ballLabel->setPixmap(ballPixmap);
	ballLabel->setFixedSize(ballPixmap.size());
	ballLabel->move(paddleLabel->x() + paddleLabel->width() / 2 - ballLabel->width() / 2, paddleLabel->y() - ballLabel->height() - 10);

	//��ʼ���Ѷ�ϵ��
	this->difficulty = difficulty;

	//ש���ʼ��
	for (int i = 0; i < 10; i++)
	{
		blockLabelVector.append(QVector<QLabel *>{});
		for (int j = 0; j < 16; j++)
		{
			QLabel *blockLabel = new QLabel(this);
			blockLabel->setPixmap(blockPixmapVector[difficulty]);
			blockLabel->setFixedSize(blockPixmapVector[difficulty].size());
			blockLabel->move(j*blockPixmapVector[difficulty].width(), i*blockPixmapVector[difficulty].height());
			blockLabelVector[blockLabelVector.size() - 1].append(blockLabel);
		}
	}

	//�����ƶ���ʱ����ʼ��
	paddleMoveLeftTimer.setInterval(10);
	paddleMoveRightTimer.setInterval(10);
	connect(&paddleMoveLeftTimer, &QTimer::timeout, this, &GameScene::paddleMoveLeftSlot);
	connect(&paddleMoveRightTimer, &QTimer::timeout, this, &GameScene::paddleMoveRightSlot);

	//���ƶ���ʱ��
	ballMoveTimer.setInterval(20);
	connect(&ballMoveTimer, &QTimer::timeout, this, &GameScene::ballMoveSlot);

	//���ƶ�����
	ballMoveDx = 5;
	ballMoveDy = 5;
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Left) //���������ƶ�
	{
		//ֻ��������Ķ�ʱ������
		paddleMoveLeftTimer.start();
		paddleMoveRightTimer.stop();
	}
	else if (event->key() == Qt::Key_Right)
	{
		paddleMoveRightTimer.start();
		paddleMoveLeftTimer.stop();
	}
}

void GameScene::keyReleaseEvent(QKeyEvent * event)
{
	//�ͷŰ�����ֹͣ�����ƶ�
	if (event->key() == Qt::Key_Left)
	{
		paddleMoveLeftTimer.stop();
	}
	else if (event->key() == Qt::Key_Right)
	{
		paddleMoveRightTimer.stop();
	}
	//��ʼ�ƶ�
	else if (event->key() == Qt::Key_Space)
	{
		ballMoveTimer.start();
	}
}

void GameScene::paddleMoveLeftSlot()
{
	int x = paddleLabel->x(); //��ȡ��ǰ��x����
	x -= 5; //�ƶ�
	if (x < 0) //�ж������ƶ��Ƿ�ᳬ���߽�
	{
		paddleLabel->move(0, paddleLabel->y());
	}
	else
	{
		paddleLabel->move(x, paddleLabel->y());
	}
}

void GameScene::paddleMoveRightSlot()
{
	int x = paddleLabel->x(); //��ȡ��ǰ��x����
	x += 5; //�ƶ�
	if (x + paddleLabel->width() > width()) //�ж������ƶ��Ƿ�ᳬ���߽�
	{
		paddleLabel->move(width() - paddleLabel->width(), paddleLabel->y());
	}
	else
	{
		paddleLabel->move(x, paddleLabel->y());
	}
}

void GameScene::ballMoveSlot()
{
	//����������
	int x = ballLabel->x() + ballMoveDx;
	int y = ballLabel->y() + ballMoveDy;

	//����򳬳��߽磬����������ڱ߽�֮�ڣ�ͬʱ�ı��ٶȷ���
	if (x + ballLabel->width() > width())
	{
		x = width() - ballLabel->width();
		ballMoveDx *= -1;
	}
	if (x < 0)
	{
		x = 0;
		ballMoveDx *= -1;
	}
	if (y + ballLabel->height() > height())
	{
		y = height() - ballLabel->height();
		ballMoveDy *= -1;
	}
	if (y < 0)
	{
		y = 0;
		ballMoveDy *= -1;
	}
	//ˢ�����λ��
	ballLabel->move(x, y);

	//�ж����Ƿ�͵�����ײ
	if (isCrash(ballLabel, paddleLabel))
	{
		ballMoveDy *= -1;
	}

	//�ж��Ƿ�ײ����ש��
	for (int i = 0; i < blockLabelVector.size(); i++)
	{
		for (int j = 0; j < blockLabelVector[i].size(); j++)
		{
			if (isCrash(ballLabel, blockLabelVector[i][j]) && !blockLabelVector[i][j]->isHidden())
			{
				ballMoveDy *= -1;
				blockLabelVector[i][j]->hide();
				goto outside;
			}
		}
	}
outside:;

	//�ж��Ƿ���Ϸ����
	if (ballLabel->y() + ballLabel->height() >= height())
	{
		//ֹͣһ��
		paddleMoveLeftTimer.stop();
		paddleMoveRightTimer.stop();
		ballMoveTimer.stop();
		//��ʾ��Ϸ������Ϣ�����������һ�ֵĻ�
		if (QMessageBox::information(this, tr(u8"��Ϸ����"), tr(u8"��Ϸ�������Ƿ��Ե�ǰ�Ѷ�����һ�֣�"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
		{
			StartScene *startScene = new StartScene(Director::getInstance()->getWindow());
			Director::getInstance()->setNowScene(startScene);
			startScene->init();
			startScene->show();
			deleteLater();
		}
		//������������һ�֣����³�ʼ��������ϷԪ������
		else
		{
			//���°ڷŵ���λ��
			paddleLabel->move(width() / 2 - paddleLabel->width() / 2, height() - paddleLabel->height() - 10);
			//���°ڷ����λ�ò������趨����ƶ�����
			ballLabel->move(paddleLabel->x() + paddleLabel->width() / 2 - ballLabel->width() / 2, paddleLabel->y() - ballLabel->height() - 10);
			ballMoveDx = 5;
			ballMoveDy = 5;
			//������ʾ���е�ש��
			for (int i = 0; i < blockLabelVector.size(); i++)
			{
				for (int j = 0; j < blockLabelVector[i].size(); j++)
				{
					blockLabelVector[i][j]->show();
				}
			}
		}
	}
}

bool GameScene::isCrash(QLabel * l1, QLabel * l2)
{
	return l1->x() >= l2->x() - l1->width() && l1->x() <= l2->x() + l2->width() && l1->y() >= l2->y() - l1->height() && l1->y() <= l2->y() + l2->height();
}