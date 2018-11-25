#ifndef CONFIG_H
#define CONFIG_H

#include "QString"

//ȫ��������
class Config
{
private:
	Config(); //��ֹĬ���Զ�����

	static Config *instance; //����ָ��

	int highestScore; //��߷�
	QString highestScorePlayer; //��߷ֱ�����
	QString themeResourceUrl; //��ǰ������Դurl

public:
	Config(const Config &) = delete;
	Config &operator=(const Config &) = delete;
	~Config();

	static Config *getInstance(); //��ȡ����ָ��

	void init(); //��ʼ�����е�����
	void uninit(); //������������

	void setTheme(QString themeResourceUrl); //���õ�ǰ����

	void setHighestScore(int highestScore); //������߷ַ���
	int getHighestScore(); //��ȡ��߷ַ���
	void setHighestScorePlayer(QString highestScorePlayer); //������߷ֱ�����
	QString getHighestScorePlayer(); //��ȡ��߷ֱ�����
};

#endif // CONFIG_H
