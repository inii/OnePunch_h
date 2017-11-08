#pragma once
#include <windows.h>
#include "dinput.h"

//input类 键盘鼠标的处理
#define DIM_LBUTTON 0   //左键
#define DIM_RBUTTON 1   //右键
#define DIM_MBUTTON 2   //中键

class CInput
{
	CInput();
public:
	~CInput();

public:
	static CInput& getInstance()
	{
		static CInput s;
		return s;
	}
	//初始化
	void init();
	//更新
	void update();
	//是否被按下
	bool keyDown(DWORD key);
	//是否被按住
	bool keyHold(DWORD key);
	//是否抬起
	bool keyUp(DWORD key);
	//是否被按下
	bool mouseDown(DWORD key);
	//是否被按住
	bool mouseHold(DWORD key);
	//是否抬起
	bool mouseUp(DWORD key);

	//鼠标的移动跟滚轮
	LONG getMouseX() {return m_curDms.lX;}
	LONG getMouseY() {return m_curDms.lY;}
	LONG getMouseWheel() {return m_curDms.lZ;}

	//释放
	void release();
	// input对象
	IDirectInput8* m_pInput;
	//键盘设备对象
	IDirectInputDevice8A* m_pKey;
	IDirectInputDevice8A* m_pMouse;

	BYTE m_lastkeyData[256];//上一帧按键数据
	BYTE m_curkeyData[256]; //当前帧按键数据

	DIMOUSESTATE m_lastDms; //鼠标的数据
	DIMOUSESTATE m_curDms; //鼠标的数据
};

