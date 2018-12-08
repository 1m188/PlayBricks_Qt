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
	fps = 30;

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
		//��ȡFPS
		temp = f.readLine();
		temp.chop(1);
		fps = temp.toInt();
		//���ƶ�ȡ������fps��Χ
		if (fps > 60)
		{
			fps = 60;
		}
		else if (fps < 30)
		{
			fps = 30;
		}
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
	//д����߷�
	f.write(QString::number(highestScore).toStdString().c_str());
	f.write("\n");
	//д����߷ֱ�����
	f.write(highestScorePlayer.toStdString().c_str());
	f.write("\n");
	//д�뵱ǰ������Դurl
	f.write(themeResourceUrl.toStdString().c_str());
	f.write("\n");
	//д�뵱ǰFPSֵ
	f.write(QString::number(fps).toStdString().c_str());
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

const int Config::getHighestScore() const
{
	return highestScore;
}

void Config::setHighestScorePlayer(QString highestScorePlayer)
{
	this->highestScorePlayer = highestScorePlayer;
}

const QString Config::getHighestScorePlayer() const
{
	return highestScorePlayer;
}

void Config::setFps(int fps)
{
	this->fps = fps;
}

const int Config::getFps() const
{
	return fps;
}