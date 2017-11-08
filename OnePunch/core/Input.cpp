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

//��ʼ��
void CInput::init()
{
	HINSTANCE hInst = CMainWnd::getInstance().getMainInst();
	HWND hWnd = CMainWnd::getInstance().getMainWnd();

	//����input����
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (LPVOID*)(&m_pInput), NULL)))
	{
		//MessageBox(hWnd, );
		return;
	}
	//���������豸����
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL)))
	{
		return;
	}

	//��������豸
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
	{
		return;
	}

	//���ü������ݸ�ʽ
	if (FAILED(m_pKey->SetDataFormat(&c_dfDIKeyboard)))
	{
		return;
	}

	//�����������ݸ�ʽ
	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return;
	}
	
	//����Э���㼶
	HWND hwnd = CMainWnd::getInstance().getMainWnd();
	m_pKey->SetCooperativeLevel(hwnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
	m_pMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND |DISCL_NONEXCLUSIVE);

	//��ȡ�豸����Ȩ
	m_pKey->Acquire();
	m_pMouse->Acquire();
}

//�Ƿ񱻰���
bool CInput::keyDown(DWORD key)
{
	return (m_curkeyData[key] & 0x80) && !(m_lastkeyData[key] & 0x80);
}

//�Ƿ񱻰�ס
bool CInput::keyHold(DWORD key)
{
	return (m_curkeyData[key] & 0x80) && (m_lastkeyData[key] & 0x80);
}
//�Ƿ�̧��
bool CInput::keyUp(DWORD key)
{
	return (!(m_curkeyData[key] & 0x80)) && (m_lastkeyData[key] & 0x80);
}

//�Ƿ񱻰���
bool CInput::mouseDown(DWORD key)
{
	return (m_curDms.rgbButtons[key] & 0x80) && !(m_lastDms.rgbButtons[key] & 0x80);
}
//�Ƿ񱻰�ס
bool CInput::mouseHold(DWORD key)
{
	return (m_curDms.rgbButtons[key] & 0x80) && (m_lastDms.rgbButtons[key] & 0x80);
}
//�Ƿ�̧��
bool CInput::mouseUp(DWORD key)
{
	return (!(m_curDms.rgbButtons[key] & 0x80)) && (m_lastDms.rgbButtons[key] & 0x80);
}

//����
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

//�ͷ�
void CInput::release()
{
	m_pKey->Unacquire();
	m_pKey->Release();
	m_pMouse->Unacquire();
	m_pMouse->Release();

	m_pInput->Release();
}