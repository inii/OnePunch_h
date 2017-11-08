#pragma once
#include <windows.h>
#include "dinput.h"

//input�� �������Ĵ���
#define DIM_LBUTTON 0   //���
#define DIM_RBUTTON 1   //�Ҽ�
#define DIM_MBUTTON 2   //�м�

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
	//��ʼ��
	void init();
	//����
	void update();
	//�Ƿ񱻰���
	bool keyDown(DWORD key);
	//�Ƿ񱻰�ס
	bool keyHold(DWORD key);
	//�Ƿ�̧��
	bool keyUp(DWORD key);
	//�Ƿ񱻰���
	bool mouseDown(DWORD key);
	//�Ƿ񱻰�ס
	bool mouseHold(DWORD key);
	//�Ƿ�̧��
	bool mouseUp(DWORD key);

	//�����ƶ�������
	LONG getMouseX() {return m_curDms.lX;}
	LONG getMouseY() {return m_curDms.lY;}
	LONG getMouseWheel() {return m_curDms.lZ;}

	//�ͷ�
	void release();
	// input����
	IDirectInput8* m_pInput;
	//�����豸����
	IDirectInputDevice8A* m_pKey;
	IDirectInputDevice8A* m_pMouse;

	BYTE m_lastkeyData[256];//��һ֡��������
	BYTE m_curkeyData[256]; //��ǰ֡��������

	DIMOUSESTATE m_lastDms; //��������
	DIMOUSESTATE m_curDms; //��������
};

