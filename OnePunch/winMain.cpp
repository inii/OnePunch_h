#include <windows.h>
#include <stdio.h>
#include "cmdline.h"
#include "gameapp.h"
#include "MainWnd.h"
#include "time.h"

int WINAPI WinMain(HINSTANCE hIns,    //�ó���ĵ�ǰ����ʵ�����
				   HINSTANCE pRevIns, //��һ�����е�ʵ�����
				   LPTSTR lpCmdLine,  //�ַ��� �����в���
				   int nCmdShow)	  //��ʾָ���Ĵ���Ӧ�������ʾ����� ��С�� ����
{
	CCmdLine& line = CCmdLine::getInstance();
	line.parse(lpCmdLine);

	CMainWnd::getInstance().CreateWnd(hIns);

	if(!CGameApp::getInstance().init())
		return 0;

	float		FPS = 60.0f; //��Ϸÿ�����ж���֡ ͨ��60
	clock_t		lasttime = clock();

	//6.��Ϣѭ��
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);//������Ϣ
			DispatchMessage(&msg); //�ַ���Ϣ �ַ�����Ϣ������������Ϣ
		}
		else 
		{
			clock_t curtime = clock();
			float dt = (curtime - lasttime) / 1000.0f;
			if (dt < 1.0f / FPS)
				continue;
			lasttime = curtime;

			//����
			CGameApp::getInstance().update(dt);
			//��Ⱦ
			CGameApp::getInstance().render();
		}
	}

	//�ͷ�
	CGameApp::getInstance().release();

	return 0;
}

