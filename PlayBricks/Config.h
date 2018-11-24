#ifndef CONFIG_H
#define CONFIG_H

#include "QString"

//ȫ��������
class Config
{
private:
	Config(); //��ֹĬ���Զ�����

	static Config *instance; //����ָ��

	int highestScore = 0; //��߷�
	QString highestScorePlayer = "None"; //��߷ֱ�����
	QString themeResourceUrl = ":/theme/Resources/theme/default.qss"; //��ǰ������Դurl

public:
	Config(const Config &) = delete;
	Config &operator=(const Config &) = delete;
	~Config();

	static Config *getInstance(); //��ȡ����ָ��

	void init(); //��ʼ�����е�����
	void uninit(); //������������

	void setHighestScore(int highestScore); //������߷ַ���
	int getHighestScore(); //��ȡ��߷ַ���
	void setHighestScorePlayer(QString highestScorePlayer); //������߷ֱ�����
	QString getHighestScorePlayer(); //��ȡ��߷ֱ�����
	void setThemeResourceUrl(QString themeResourceUrl); //���õ�ǰ������Դurl
	QString getThemeResourceUrl(); //��ȡ��ǰ������Դurl
};

#endif // CONFIG_H
