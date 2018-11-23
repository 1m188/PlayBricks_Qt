#include "Config.h"
#include "QFile"
#include "QTextStream"

Config *Config::instance = nullptr; //��ʼ������ָ��

Config::Config() :highestScore(0), highestScorePlayer("None")
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
	QFile f("config.ini");
	//����ļ����ڵĻ����ȡ�������
	if (f.exists())
	{
		f.open(QIODevice::ReadOnly);
		QTextStream ts(&f);
		ts >> highestScore; //��ȡ��߷�
		ts >> highestScorePlayer; //��ȡ��߷ֱ�����
		f.close();
	}
	//���򴴽������ļ�����ʹ��Ĭ�ϵĳ�ʼ�����ý�����Ϸ
	else
	{
		f.open(QIODevice::WriteOnly);
		f.close();
	}
}

void Config::uninit()
{
	QFile f("config.ini");
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream ts(&f);
	ts << highestScore << ' '; //д����߷�
	ts << highestScorePlayer << ' '; //д����߷ֱ�����
	f.close();
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
