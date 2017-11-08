#include "CmdLine.h"

CCmdLine::~CCmdLine()
{
}

//����������
void CCmdLine::parse(const char* line)
{
	m_iScreenW = 1280;
	m_iScreenH = 720;

	strcpy(m_strLine, line);

	int len = strlen(m_strLine);
	char * pTemp = new char[len+1];
	memset(pTemp, 0, len+1);
	strcpy(pTemp, m_strLine);

	char *s = strtok(pTemp, " ");
	if (s != nullptr)
	{
		m_iScreenW = atoi(s);//���ڿ�
		s = strtok(nullptr, " ");

		if (s == nullptr)
		{
			m_iScreenH = m_iScreenW / 1.778;
		}
		else
		{
			m_iScreenH = atoi(s);//���ڸ�
		}
	}
}