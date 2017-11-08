#pragma once
#include <windows.h>
#include <map>
#include <string>
#include <functional>
using namespace std;

//主窗口类
class CMainWnd
{
	CMainWnd();
public:
	~CMainWnd();

	static CMainWnd& getInstance() {
		static CMainWnd s;
		return s;
	}

	BOOL CreateWnd(HINSTANCE hIns);

	//获取光标位置
	POINT getCursorPos();

	HWND getMainWnd() { return mHwnd; }
	HINSTANCE getMainInst() { return mHIns; }

	static void insertFunc(const string& name, const std::function<void(UINT, WPARAM)>& p) {
		auto it = mClickCallbacks.find(name);
		if (it != mClickCallbacks.end()) {
			//插入失败
			return;
		}
		mClickCallbacks[name] = p;
	}

	static void removeFunc(const string& name) {
		auto it = mClickCallbacks.find(name);
		if (it != mClickCallbacks.end())
		{
			mClickCallbacks.erase(it);
		}
	}

private:

	static std::map<string, std::function<void(UINT,WPARAM)>> mClickCallbacks;

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

	HWND mHwnd;
	HINSTANCE mHIns;
};

