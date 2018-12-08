#include "GameScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QKeyEvent"
#include "QMessageBox"
#include "QInputDialog"
#include "QPainter"

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
	this->difficulty = difficulty % 3; //��ֹ����Ĳ�����������

	//�÷ֳ�ʼ��
	nowScore = 0;

	//�������ı��߶ȳ�ʼ��
	scoreTextHeight = 20;

	//֡����ʼ��
	fps = Config::getInstance()->getFps();

	//�����ʼ��
	paddle = Paddle(width() / 2 - paddlePixmap.width() / 2, height() - paddlePixmap.height() - 10, paddlePixmap.width(), paddlePixmap.height(), paddlePixmap, (15 - this->difficulty * 2) * 30 / fps, false, false);

	//���ʼ��
	ball = Ball(paddle.getX() + paddle.getWidth() / 2 - ballPixmap.width() / 2, paddle.getY() - ballPixmap.height() - 10, ballPixmap.width(), ballPixmap.height(), ballPixmap, (this->difficulty * 3 + 5) * 30 / fps, (this->difficulty * 3 + 5) * 30 / fps, false);

	//ש���ʼ��
	for (int i = 0; i < this->difficulty * 4 + 10; i++)
	{
		bricksVector.append(QVector<Brick>{});
		for (int j = 0; j < 16; j++)
		{
			Brick brick(j*bricksImageVector.at(this->difficulty).width(), scoreTextHeight + i*bricksImageVector.at(this->difficulty).height(), bricksImageVector.at(this->difficulty).width(), bricksImageVector.at(this->difficulty).height(), bricksImageVector.at(this->difficulty), false);
			bricksVector[bricksVector.size() - 1].append(brick);
		}
	}

	//��ʼ����������ʱ��
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &GameScene::gameCycle);
	timer->setInterval(1000 / fps);
	timer->start();
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

void GameScene::paintEvent(QPaintEvent *event)
{
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
			//û�б�ײ���ĲŻ���
			if (!brick.getIsCollided())
			{
				painter->drawPixmap(brick.getX(), brick.getY(), brick.getImage());
			}
		}
	}

	//���Ʒ���
	painter->setPen(Qt::red);
	painter->setFont(QFont(u8"΢���ź�", 12));
	painter->drawText(0, 0, width(), scoreTextHeight, Qt::AlignCenter, QString(u8"������%1").arg(nowScore));

	painter->end();

	Scene::paintEvent(event);
}

void GameScene::gameCycle()
{
	//����״̬
	//�����ƶ�
	if (paddle.getIsLefting())
	{
		paddle.setX(paddle.getX() - paddle.getDx());
	}
	if (paddle.getIsRighting())
	{
		paddle.setX(paddle.getX() + paddle.getDx());
	}

	//����������ͼ�߽�
	if (paddle.getX() < 0)
	{
		paddle.setX(0);
	}
	else if (paddle.getX() + paddle.getWidth() > width())
	{
		paddle.setX(width() - paddle.getWidth());
	}

	//���ƶ�
	if (ball.getIsMoving())
	{
		ball.setX(ball.getX() + ball.getDx());
		ball.setY(ball.getY() + ball.getDy());
	}

	//��������ͼ�߽�
	//������߽�
	if (ball.getX() < 0)
	{
		ball.setX(0);
		ball.setDx(ball.getDx()*-1);
	}
	//�����ұ߽�
	else if (ball.getX() + ball.getWidth() > width())
	{
		ball.setX(width() - ball.getWidth());
		ball.setDx(ball.getDx()*-1);
	}
	//�����ϱ߽�
	else if (ball.getY() < scoreTextHeight)
	{
		ball.setY(scoreTextHeight);
		ball.setDy(ball.getDy()*-1);
	}

	//���Ƿ�͵�����ײ
	if (isCrash(ball, paddle))
	{
		updateBallDxy(paddle);
	}

	//���Ƿ��ש����ײ
	for (auto &vector : bricksVector)
	{
		for (Brick &brick : vector)
		{
			if (isCrash(ball, brick) && !brick.getIsCollided())
			{
				updateBallDxy(brick);
				brick.setIsCollided(true);
				nowScore += difficulty + 1;
				goto outside;
			}
		}
	}
outside:;

	//��Ϸ�Ƿ����
	//�����
	if (ball.getY() + ball.getHeight() >= height())
	{
		//ֹͣ���»���
		timer->stop();

		//��Ϸ����֮�����Ϊ��߷ֵĻ���������߷ֺ���߷ֱ�����
		if (nowScore > Config::getInstance()->getHighestScore())
		{
			Config::getInstance()->setHighestScore(nowScore);
			Config::getInstance()->setHighestScorePlayer(QInputDialog::getText(this, tr(u8"��߷�"), tr(u8"��ķ�����%1����ϲ���Ϊ��߷֣�������������մ�����").arg(nowScore)));
		}
		//��ʾ��Ϸ������Ϣ�����������һ�ֵĻ��ص���ʼ����
		if (QMessageBox::information(this, tr(u8"��Ϸ����"), tr(u8"��Ϸ��������ķ�����%1���Ƿ��Ե�ǰ�Ѷ�����һ�֣�").arg(nowScore), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
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
			//�������õ���״̬
			paddle.setX(width() / 2 - paddle.getWidth() / 2);
			paddle.setY(height() - paddle.getHeight() - 10);
			paddle.setIsLefting(false);
			paddle.setIsRighting(false);

			//�����������״̬
			ball.setX(paddle.getX() + paddle.getWidth() / 2 - ball.getWidth() / 2);
			ball.setY(paddle.getY() - ball.getHeight() - 10);
			ball.setDx((this->difficulty * 3 + 5) * 30 / fps);
			ball.setDy((this->difficulty * 3 + 5) * 30 / fps);
			ball.setIsMoving(false);

			//���³�ʼ������
			nowScore = 0;

			//������ʾ���е�ש��
			for (auto &vector : bricksVector)
			{
				for (Brick &brick : vector)
				{
					brick.setIsCollided(false);
				}
			}

			//��ʼ���»���
			timer->start();
		}
	}
	//ש�����
	else
	{
		//��ÿ��ש������жϣ������ש����ʾ��û���򣩵Ļ�������ȥ���������ש�����֮�����Ϊ
		for (auto &vector : bricksVector)
		{
			for (Brick &brick : vector)
			{
				if (!brick.getIsCollided())
				{
					goto judgeEnd;
				}
			}
		}

		//���˷���������ˢ��֮�⣬����������ˢ������һ�飬ֱ��ĳһ�������Ϊֹ���˼�ķ���һֱ�ۼ�
		//�������õ���״̬
		paddle.setX(width() / 2 - paddle.getWidth() / 2);
		paddle.setY(height() - paddle.getHeight() - 10);
		paddle.setIsLefting(false);
		paddle.setIsRighting(false);

		//�����������״̬
		ball.setX(paddle.getX() + paddle.getWidth() / 2 - ball.getWidth() / 2);
		ball.setY(paddle.getY() - ball.getHeight() - 10);
		ball.setDx((this->difficulty * 3 + 5) * 30 / fps);
		ball.setDy((this->difficulty * 3 + 5) * 30 / fps);
		ball.setIsMoving(false);

		//������ʾ���е�ש��
		for (auto &vector : bricksVector)
		{
			for (Brick &brick : vector)
			{
				brick.setIsCollided(false);
			}
		}
	}
judgeEnd:;

	//����
	update();
}

bool GameScene::isCrash(Sprite s1, Sprite s2) const
{
	return s1.getX() >= s2.getX() - s1.getWidth() && s1.getX() <= s2.getX() + s2.getWidth() && s1.getY() >= s2.getY() - s1.getHeight() && s1.getY() <= s2.getY() + s2.getHeight();
}

void GameScene::updateBallDxy(Sprite s)
{
	//��ȡ���������ײ��ʱ��Ĺ�ͬ�Ŀ�͸�
	int overWidth = ((ball.getX() + ball.getWidth() < s.getX() + s.getWidth()) ? (ball.getX() + ball.getWidth()) : (s.getX() + s.getWidth())) - (ball.getX() > s.getX() ? ball.getX() : s.getX());
	int overHeight = ((ball.getY() + ball.getHeight() < s.getY() + s.getHeight()) ? (ball.getY() + ball.getHeight()) : (s.getY() + s.getHeight())) - (ball.getY() > s.getY() ? ball.getY() : s.getY());
	//�ж��ı߸���������ǿ�˵���������Ӧ�Ǵ��ϻ�������ײ�ģ�����Ӧ����������ײ�������������ȫ����
	if (overWidth > overHeight)
	{
		ball.setDy(ball.getDy()*-1);
	}
	else if (overWidth < overHeight)
	{
		ball.setDx(ball.getDx()*-1);
	}
	else
	{
		ball.setDx(ball.getDx()*-1);
		ball.setDy(ball.getDy()*-1);
	}
}