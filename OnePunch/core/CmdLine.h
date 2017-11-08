#pragma once
#include <string>

//命令行参数类
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

	//分析命令行
	void parse(const char* line);

	int getScreenW() {return m_iScreenW;}
	int getScreenH() {return m_iScreenH;}

private:

	int m_iScreenW;
	int m_iScreenH;
	char m_strLine[255];
};

