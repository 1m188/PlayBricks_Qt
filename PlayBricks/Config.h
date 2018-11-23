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
};

#endif // CONFIG_H
