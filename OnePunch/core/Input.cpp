#include "Input.h"
#include "D3DDevice.h"
#include "MainWnd.h"

CInput::CInput()
{
	memset(m_lastkeyData, 0, sizeof(m_lastkeyData));
	memset(m_curkeyData, 0, sizeof(m_curkeyData));

	memset(&m_lastDms, 0, sizeof(m_lastDms));
	memset(&m_curDms, 0, sizeof(m_curDms));
}

CInput::~CInput()
{
}

//初始化
void CInput::init()
{
	HINSTANCE hInst = CMainWnd::getInstance().getMainInst();
	HWND hWnd = CMainWnd::getInstance().getMainWnd();

	//创建input对象
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (LPVOID*)(&m_pInput), NULL)))
	{
		//MessageBox(hWnd, );
		return;
	}
	//创建键盘设备对象
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL)))
	{
		return;
	}

	//创建鼠标设备
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
	{
		return;
	}

	//设置键盘数据格式
	if (FAILED(m_pKey->SetDataFormat(&c_dfDIKeyboard)))
	{
		return;
	}

	//设置鼠标的数据格式
	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return;
	}
	
	//设置协调层级
	HWND hwnd = CMainWnd::getInstance().getMainWnd();
	m_pKey->SetCooperativeLevel(hwnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	m_pMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND |DISCL_NONEXCLUSIVE);

	//获取设备控制权
	m_pKey->Acquire();
	m_pMouse->Acquire();
}

//是否被按下
bool CInput::keyDown(DWORD key)
{
	return (m_curkeyData[key] & 0x80) && !(m_lastkeyData[key] & 0x80);
}

//是否被按住
bool CInput::keyHold(DWORD key)
{
	return (m_curkeyData[key] & 0x80) && (m_lastkeyData[key] & 0x80);
}
//是否抬起
bool CInput::keyUp(DWORD key)
{
	return (!(m_curkeyData[key] & 0x80)) && (m_lastkeyData[key] & 0x80);
}

//是否被按下
bool CInput::mouseDown(DWORD key)
{
	return (m_curDms.rgbButtons[key] & 0x80) && !(m_lastDms.rgbButtons[key] & 0x80);
}
//是否被按住
bool CInput::mouseHold(DWORD key)
{
	return (m_curDms.rgbButtons[key] & 0x80) && (m_lastDms.rgbButtons[key] & 0x80);
}
//是否抬起
bool CInput::mouseUp(DWORD key)
{
	return (!(m_curDms.rgbButtons[key] & 0x80)) && (m_lastDms.rgbButtons[key] & 0x80);
}

//更新
void CInput::update()
{
	memcpy(m_lastkeyData, m_curkeyData, sizeof(m_curkeyData));
	memset(m_curkeyData, 0, sizeof(m_curkeyData));
	if (DI_OK != m_pKey->GetDeviceState(sizeof(m_curkeyData), m_curkeyData))
	{
		memset(m_curkeyData, 0, sizeof(m_curkeyData));
		m_pKey->Acquire();
	}

	memcpy(&m_lastDms, &m_curDms, sizeof(m_curDms));
	memset(&m_curDms,0,sizeof(m_curDms));
	if (DI_OK != m_pMouse->GetDeviceState(sizeof(m_curDms), &m_curDms))
	{
		memset(&m_curDms, 0, sizeof(m_curDms));
		m_pMouse->Acquire();
	}
}

//释放
void CInput::release()
{
	m_pKey->Unacquire();
	m_pKey->Release();
	m_pMouse->Unacquire();
	m_pMouse->Release();

	m_pInput->Release();
}