#include "Config.h"
#include "QFile"
#include "QTextStream"
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
	QFile f("config.ini");
	//����ļ����ڵĻ����ȡ�������
	if (f.exists())
	{
		f.open(QIODevice::ReadOnly);
		QTextStream ts(&f);
		ts >> highestScore; //��ȡ��߷�
		ts >> highestScorePlayer; //��ȡ��߷ֱ�����
		ts >> themeResourceUrl; //��ȡ��ǰ������Դurl
		f.close();
	}
	//���򴴽������ļ�����ʹ��Ĭ�ϵĳ�ʼ�����ý�����Ϸ
	else
	{
		f.open(QIODevice::WriteOnly);
		f.close();
	}

	//��ʼ��ʱ�����õ�ǰ����
	QFile themeFile(themeResourceUrl);
	themeFile.open(QIODevice::ReadOnly);
	qApp->setStyleSheet(themeFile.readAll());
	themeFile.close();
}

void Config::uninit()
{
	QFile f("config.ini");
	f.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream ts(&f);
	ts << highestScore << ' '; //д����߷�
	ts << highestScorePlayer << ' '; //д����߷ֱ�����
	ts << themeResourceUrl << ' '; //д�뵱ǰ������Դurl
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

void Config::setThemeResourceUrl(QString themeResourceUrl)
{
	this->themeResourceUrl = themeResourceUrl;
}

QString Config::getThemeResourceUrl()
{
	return themeResourceUrl;
}