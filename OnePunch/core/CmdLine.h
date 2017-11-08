#pragma once
#include <string>

//�����в�����
class CCmdLine
{
	CCmdLine() {};
public:
	static CCmdLine& getInstance()
	{
		static CCmdLine s;
		return s;
	}
	~CCmdLine();

	//����������
	void parse(const char* line);

	int getScreenW() {return m_iScreenW;}
	int getScreenH() {return m_iScreenH;}

private:

	int m_iScreenW;
	int m_iScreenH;
	char m_strLine[255];
};

