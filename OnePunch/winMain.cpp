#include <windows.h>
#include <stdio.h>
#include "cmdline.h"
#include "gameapp.h"
#include "MainWnd.h"
#include "time.h"

int WINAPI WinMain(HINSTANCE hIns,    //该程序的当前运行实例句柄
				   HINSTANCE pRevIns, //上一个运行的实例句柄
				   LPTSTR lpCmdLine,  //字符串 命令行参数
				   int nCmdShow)	  //表示指定的窗口应该如何显示，最大化 最小化 隐藏
{
	CCmdLine& line = CCmdLine::getInstance();
	line.parse(lpCmdLine);

	CMainWnd::getInstance().CreateWnd(hIns);

	if(!CGameApp::getInstance().init())
		return 0;

	float		FPS = 60.0f; //游戏每秒运行多少帧 通常60
	clock_t		lasttime = clock();

	//6.消息循环
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);//翻译信息
			DispatchMessage(&msg); //分发信息 分发给消息处理函数处理消息
		}
		else 
		{
			clock_t curtime = clock();
			float dt = (curtime - lasttime) / 1000.0f;
			if (dt < 1.0f / FPS)
				continue;
			lasttime = curtime;

			//更新
			CGameApp::getInstance().update(dt);
			//渲染
			CGameApp::getInstance().render();
		}
	}

	//释放
	CGameApp::getInstance().release();

	return 0;
}

