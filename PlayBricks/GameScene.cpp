#include "GameScene.h"
#include "Director.h"
#include "Config.h"
#include "StartScene.h"
#include "QApplication"
#include "QDeskTopWidget"
#include "QKeyEvent"
#include "QMessageBox"
#include "QInputDialog"

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
	ballPixmap.load(":/game/Resources/ball.png");
	paddlePixmap.load(":/game/Resources/paddle.png");
	blockPixmapVector.resize(3);
	blockPixmapVector[0].load(":/game/Resources/block_green.png");
	blockPixmapVector[1].load(":/game/Resources/block_blue.png");
	blockPixmapVector[2].load(":/game/Resources/block_red.png");

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
	difficulty %= 3; //��ֹ������Ѷ�ϵ��������Χ
	this->difficulty = difficulty;

	//�÷ֳ�ʼ��
	nowScore = 0;
	scoreLabel = new QLabel(this);
	scoreLabel->setAlignment(Qt::AlignCenter);
	scoreLabel->setFont(QFont(u8"΢���ź�", 13, 8));
	QPalette p;
	p.setColor(QPalette::WindowText, Qt::red);
	scoreLabel->setPalette(p);
	scoreLabel->setText(tr(u8"������%1").arg(nowScore));
	scoreLabel->resize(width(), scoreLabel->sizeHint().height());
	scoreLabel->move(0, 0);

	//ש���ʼ��
	for (int i = 0; i < difficulty * 4 + 10; i++)
	{
		blockLabelVector.append(QVector<QLabel *>{});
		for (int j = 0; j < 16; j++)
		{
			QLabel *blockLabel = new QLabel(this);
			blockLabel->setPixmap(blockPixmapVector[difficulty]);
			blockLabel->setFixedSize(blockPixmapVector[difficulty].size());
			blockLabel->move(j*blockPixmapVector[difficulty].width(), scoreLabel->height() + i*blockPixmapVector[difficulty].height());
			blockLabelVector[blockLabelVector.size() - 1].append(blockLabel);
		}
	}

	//�����ƶ���ʱ����ʼ��
	paddleMoveLeftTimer.setInterval(10);
	paddleMoveRightTimer.setInterval(10);
	connect(&paddleMoveLeftTimer, &QTimer::timeout, this, [=]() {paddleMove(-paddleMoveDx); }); //�����ֵ������������ĺ����������Ҫ�ķ�const��ֵ�Ҹ�
	connect(&paddleMoveRightTimer, &QTimer::timeout, this, [=]() {paddleMove(paddleMoveDx); });

	//��ÿ���ƶ���ʱ��������ʼ��
	ballMoveTimer.setInterval(20);
	connect(&ballMoveTimer, &QTimer::timeout, this, &GameScene::ballMoveSlot);

	//��ÿ����������ƶ��ľ���
	ballMoveDxy = { static_cast<int>(difficulty) * 2 + 5 ,static_cast<int>(difficulty) * 2 + 5 };

	//����ÿ���ƶ�����
	paddleMoveDx = 6 - difficulty;
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
	//���������ƶ�
	if (event->key() == Qt::Key_Left && !event->isAutoRepeat())
	{
		//�����ƶ���ʱ��ȡ�������ƶ�
		paddleMoveLeftTimer.start();
		paddleMoveRightTimer.stop();
	}
	//���������ƶ�
	else if (event->key() == Qt::Key_Right && !event->isAutoRepeat())
	{
		//�����ƶ���ʱ��ȡ�������ƶ�
		paddleMoveRightTimer.start();
		paddleMoveLeftTimer.stop();
	}
	//��ס�ո�������
	else if (event->key() == Qt::Key_Space && !event->isAutoRepeat())
	{
		ballMoveDxy.first *= 3;
		ballMoveDxy.second *= 3;
	}
	//��������ͷź���ʼ�ƶ�
	if (!event->isAutoRepeat())
	{
		ballMoveTimer.start();
	}
}

void GameScene::keyReleaseEvent(QKeyEvent * event)
{
	//����ֹͣ�����ƶ�
	if (event->key() == Qt::Key_Left && !event->isAutoRepeat())
	{
		paddleMoveLeftTimer.stop();
	}
	//����ֹͣ�����ƶ�
	else if (event->key() == Qt::Key_Right && !event->isAutoRepeat())
	{
		paddleMoveRightTimer.stop();
	}
	//�ͷſո������ص�ԭ�����ٶ�
	else if (event->key() == Qt::Key_Space && !event->isAutoRepeat())
	{
		ballMoveDxy.first /= 3;
		ballMoveDxy.second /= 3;
	}
}

void GameScene::ballMoveSlot()
{
	//����������
	int x = ballLabel->x() + ballMoveDxy.first;
	int y = ballLabel->y() + ballMoveDxy.second;

	//����򳬳��߽磬����������ڱ߽�֮�ڣ�ͬʱ�ı��ٶȷ���
	if (x + ballLabel->width() > width())
	{
		x = width() - ballLabel->width();
		ballMoveDxy.first *= -1;
	}
	if (x < 0)
	{
		x = 0;
		ballMoveDxy.first *= -1;
	}
	if (y + ballLabel->height() > height())
	{
		y = height() - ballLabel->height();
		ballMoveDxy.second *= -1;
	}
	if (y < scoreLabel->height())
	{
		y = 0;
		ballMoveDxy.second *= -1;
	}
	//ˢ�����λ��
	ballLabel->move(x, y);

	//�ж����Ƿ�͵�����ײ
	if (isCrash(ballLabel, paddleLabel))
	{
		updateBallMoveDxy(paddleLabel);
	}

	//�ж��Ƿ�ײ����ש��
	for (int i = 0; i < blockLabelVector.size(); i++)
	{
		for (int j = 0; j < blockLabelVector[i].size(); j++)
		{
			if (isCrash(ballLabel, blockLabelVector[i][j]) && !blockLabelVector[i][j]->isHidden())
			{
				updateBallMoveDxy(blockLabelVector[i][j]);
				blockLabelVector[i][j]->hide();
				nowScore += difficulty + 1;
				scoreLabel->setText(tr(u8"������%1").arg(nowScore));
				goto outside;
			}
		}
	}
outside:;

	//�ж��Ƿ���Ϸ����
	//�����
	if (ballLabel->y() + ballLabel->height() >= height())
	{
		//ֹͣһ��
		paddleMoveLeftTimer.stop();
		paddleMoveRightTimer.stop();
		ballMoveTimer.stop();
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
			//���°ڷŵ���λ��
			paddleLabel->move(width() / 2 - paddleLabel->width() / 2, height() - paddleLabel->height() - 10);
			//���°ڷ����λ�ò������趨����ƶ�����
			ballLabel->move(paddleLabel->x() + paddleLabel->width() / 2 - ballLabel->width() / 2, paddleLabel->y() - ballLabel->height() - 10);
			ballMoveDxy = { static_cast<int>(difficulty) * 2 + 5 ,static_cast<int>(difficulty) * 2 + 5 };
			//���³�ʼ������
			nowScore = 0;
			scoreLabel->setText(tr(u8"������%1").arg(nowScore));
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
	//ש�����
	else
	{
		//��ÿ��ש������жϣ������ש����ʾ��û���򣩵Ļ�������ȥ���������ש�����֮�����Ϊ
		for (int i = 0; i < blockLabelVector.size(); i++)
		{
			for (int j = 0; j < blockLabelVector[i].size(); j++)
			{
				if (!blockLabelVector[i][j]->isHidden())
				{
					goto judgeEnd;
				}
			}
		}
		//���˷���������ˢ��֮�⣬����������ˢ������һ�飬ֱ��ĳһ�������Ϊֹ���˼�ķ���һֱ�ۼ�
		//���°ڷŵ���λ��
		paddleLabel->move(width() / 2 - paddleLabel->width() / 2, height() - paddleLabel->height() - 10);
		//���°ڷ����λ�ò������趨����ƶ�����
		ballLabel->move(paddleLabel->x() + paddleLabel->width() / 2 - ballLabel->width() / 2, paddleLabel->y() - ballLabel->height() - 10);
		ballMoveDxy = { static_cast<int>(difficulty) * 2 + 5 ,static_cast<int>(difficulty) * 2 + 5 };
		//������ʾ���е�ש��
		for (int i = 0; i < blockLabelVector.size(); i++)
		{
			for (int j = 0; j < blockLabelVector[i].size(); j++)
			{
				blockLabelVector[i][j]->show();
			}
		}
	}
judgeEnd:;
}

void GameScene::paddleMove(int distance)
{
	int x = paddleLabel->x(); //��ȡ���嵱ǰ���½ǵ�x����
	x += distance; //�����ƶ�
	//�ж��Ƿ񳬳���ͼ��Χ
	if (x < 0)
	{
		x = 0;
	}
	else if (x > width() - paddleLabel->width())
	{
		x = width() - paddleLabel->width();
	}
	//�ƶ�
	paddleLabel->move(x, paddleLabel->y());
}

bool GameScene::isCrash(QLabel * l1, QLabel * l2)
{
	return l1->x() >= l2->x() - l1->width() && l1->x() <= l2->x() + l2->width() && l1->y() >= l2->y() - l1->height() && l1->y() <= l2->y() + l2->height();
}

void GameScene::updateBallMoveDxy(QLabel * sth)
{
	//��ȡ���������ײ��ʱ��Ĺ�ͬ�Ŀ�͸�
	int overWidth = ((ballLabel->x() + ballLabel->width() < sth->x() + sth->width()) ? (ballLabel->x() + ballLabel->width()) : (sth->x() + sth->width())) - (ballLabel->x() > sth->x() ? ballLabel->x() : sth->x());
	int overHeight = ((ballLabel->y() + ballLabel->height() < sth->y() + sth->height()) ? (ballLabel->y() + ballLabel->height()) : (sth->y() + sth->height())) - (ballLabel->y() > sth->y() ? ballLabel->y() : sth->y());
	//�ж��ı߸���������ǿ�˵���������Ӧ�Ǵ��ϻ�������ײ�ģ�����Ӧ����������ײ�������������ȫ����
	if (overWidth > overHeight)
	{
		ballMoveDxy.second *= -1;
	}
	else if (overWidth < overHeight)
	{
		ballMoveDxy.first *= -1;
	}
	else
	{
		ballMoveDxy.first *= -1;
		ballMoveDxy.second *= -1;
	}
}