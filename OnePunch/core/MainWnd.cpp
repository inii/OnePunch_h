#include "MainWnd.h"
#include "CmdLine.h"
#include "resource.h"

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

BOOL CMainWnd::CreateWnd(HINSTANCE hIns)
{
	mHIns = hIns;

	//1. 定义窗口类结构
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.hIcon = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));//small
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)wndProc;//窗口的消息处理函数指针
	wc.hInstance = hIns;
	wc.hCursor = LoadCursorFromFile(".\\cursor\\Arrow.ani");
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "sss";
	wc.lpszMenuName = "";
	RegisterClassEx(&wc);//2. 注册窗口类

	int w = GetSystemMetrics(0);//获取分辨率宽
	int h = GetSystemMetrics(1);//获取分辨率高

	auto line = CCmdLine::getInstance();
	int winW = line.getScreenW();
	int winH = line.getScreenH();

	winW += 16;
	winH += 35;

	//3. 创建窗口 
	mHwnd = CreateWindow("sss", //窗口类名
		"一拳超人",      //窗口标题名
		WS_CAPTION| WS_SYSMENU|WS_MINIMIZE| WS_POPUP,//窗口的风格
		(w - winW) / 2, (h - winH) / 2, winW, winH, //左上位置 和 宽高
		NULL,//父窗口的句柄
		NULL,//窗口菜单
		hIns,//当前应用程序的句柄
		NULL);

	if (!mHwnd) {
		OutputDebugString("创建窗口失败！！\n");
		return false;
	}

	HMENU hMenu = LoadMenu(hIns, MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(mHwnd, hMenu);

	//4.显示窗口
	ShowWindow(mHwnd, 10);
	//5.更新窗口
	UpdateWindow(mHwnd);

	return true;
}

//获取光标位置
POINT CMainWnd::getCursorPos()
{
	POINT pt;
	::GetCursorPos(&pt);
	HWND wnd = CMainWnd::getInstance().getMainWnd();
	ScreenToClient(wnd, &pt);
	pt.x -= 9;//修正窗口边框位置
	pt.y -= 9;
	return pt;
}

//静态的对象定义
std::map<string, std::function<void(UINT, WPARAM)>> CMainWnd::mClickCallbacks;
//消息处理函数
LRESULT CALLBACK CMainWnd::wndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case ID_40001:
			MessageBox(hWnd, "点击测试", "测试", MB_OK);
			break;
		case ID_40002:
			MessageBox(hWnd, "点击保存", "测试", MB_OK);
			break;
		case ID_AAAA_CCCC:
			MessageBox(hWnd, "AAAA", "测试", MB_OK);
			break;
		case ID_40004:
			MessageBox(hWnd, "BBBB", "测试", MB_OK);
			break;
		}
			break;
	case WM_CHAR:
	case WM_KEYDOWN:
		for (auto it = mClickCallbacks.begin(); it != mClickCallbacks.end(); it++) {
			auto p = it->second;
			p(message, wp);
		}
		break;
	case WM_DESTROY:
		PostMessage(hWnd, WM_QUIT, 0, 0);
		return S_OK;
	}
	return DefWindowProc(hWnd, message, wp, lp);//默认消息处理函数
}