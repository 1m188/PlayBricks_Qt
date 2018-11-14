#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "QPixmap"
#include "QLabel"
#include "QTimer"

//游戏主场景
class GameScene : public Scene
{
	Q_OBJECT

private:
	//一系列资源图片
	QPixmap ballPixmap;
	QPixmap paddlePixmap;
	QVector<QPixmap> blockPixmapVector;

	QLabel *ballLabel; //球
	QLabel *paddleLabel; //挡板
	QVector<QVector<QLabel *>> blockLabelVector; //砖块二维数组

	int difficulty; //难度

	//挡板移动定时器
	QTimer paddleMoveLeftTimer; //左
	QTimer paddleMoveRightTimer; //右
	QTimer ballMoveTimer; //球移动定时器

	int ballMoveDx; //球每次在x方向移动的距离
	int ballMoveDy; //球每次在y方向移动的距离
	int paddleMoveDx; //挡板在横向方向每次移动的距离

	bool isCrash(QLabel *l1, QLabel *l2); //是否碰撞

public:
	GameScene(Window *parent);
	~GameScene();

	void init(int difficulty); //初始化，传入难度，目前有0，1，2三个阶位

protected:
	void keyPressEvent(QKeyEvent *event) override; //重写按键事件
	void keyReleaseEvent(QKeyEvent *event) override; //...释放按键...

	private slots:
	void paddleMoveLeftSlot(); //挡板向左移动信号槽
	void paddleMoveRightSlot(); //...右...
	void ballMoveSlot(); //球移动
};

#endif // GAMESCENE_H
