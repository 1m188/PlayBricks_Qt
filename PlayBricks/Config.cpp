#include "Config.h"
#include "QFile"
#include "QApplication"

Config *Config::instance = nullptr; //��ʼ������ָ��

Config::Config()
{

}

Config::~Config()
{

}

Config * Config::getInstance()
{
	if (!instance)
	{
		instance = new Config();
	}
	return instance;
}

void Config::init()
{
	//��ʼ��Ĭ������
	highestScore = 0;
	highestScorePlayer = "None";
	themeResourceUrl = ":/theme/Resources/theme/default.qss";

	QFile f("config.ini");
	//����ļ����ڵĻ����ȡ�������
	if (f.exists())
	{
		f.open(QIODevice::ReadOnly);
		QString temp;
		//��ȡ��߷�
		temp = f.readLine();
		temp.chop(1);
		highestScore = temp.toInt();
		//��ȡ��߷ֱ�����
		temp = f.readLine();
		temp.chop(1);
		highestScorePlayer = temp;
		//��ȡ��ǰ������Դurl
		temp = f.readLine();
		temp.chop(1);
		themeResourceUrl = temp;
		f.close();
	}
	//���򴴽������ļ�����ʹ��Ĭ�ϵĳ�ʼ�����ý�����Ϸ
	else
	{
		f.open(QIODevice::WriteOnly);
		f.close();
	}

	//��ʼ��ʱ�����õ�ǰ����
	setTheme(themeResourceUrl);
}

void Config::uninit()
{
	QFile f("config.ini");
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	f.write(QString::number(highestScore).toStdString().c_str()); //д����߷�
	f.write("\n");
	f.write(highestScorePlayer.toStdString().c_str()); //д����߷ֱ�����
	f.write("\n");
	f.write(themeResourceUrl.toStdString().c_str()); //д�뵱ǰ������Դurl
	f.write("\n");
	f.close();
}

void Config::setTheme(QString themeResourceUrl)
{
	QFile f(themeResourceUrl);
	f.open(QIODevice::ReadOnly);
	qApp->setStyleSheet(f.readAll());
	f.close();
	this->themeResourceUrl = themeResourceUrl;
}

void Config::setHighestScore(int highestScore)
{
	this->highestScore = highestScore;
}

int Config::getHighestScore()
{
	return highestScore;
}

void Config::setHighestScorePlayer(QString highestScorePlayer)
{
	this->highestScorePlayer = highestScorePlayer;
}

QString Config::getHighestScorePlayer()
{
	return highestScorePlayer;
}