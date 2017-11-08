#include "Camera.h"
#include <d3d9.h>
#include <d3dx9math.h>
#include "D3DDevice.h"
#include "input.h"
#include "CmdLine.h"

CCamera::CCamera()
{
	m_pDevice = CD3DDevice::getInstance().getDevice();
	m_vLookat = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	m_fLongitude = D3DX_PI; //经度
	m_fLatitude = 30*D3DX_PI/180;  //纬度
	m_fDistance = 3;  //距离
	m_fRate = 0.01f;

	m_fAngle = D3DX_PI / 3;
	
	float w = CCmdLine::getInstance().getScreenW();
	float h = CCmdLine::getInstance().getScreenH();
	m_fAspectRatio = w/h;

	m_fFarZ = 5000.0f;
	m_fNearZ = 0.3f;
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
	CInput& input = CInput::getInstance();

	if (input.mouseHold(DIM_RBUTTON))
	{
		LONG x = input.getMouseX();
		LONG y = input.getMouseY();

		m_fLongitude += (x*m_fRate); //经度
		m_fLatitude  += (y*m_fRate); //纬度

		if (m_fLatitude > 60 * D3DX_PI / 180) {
			m_fLatitude = 60 * D3DX_PI / 180;
		}

		if (m_fLatitude < -60 * D3DX_PI / 180) {
			m_fLatitude = -60 * D3DX_PI / 180;
		}
	}

	LONG wheel = input.getMouseWheel();
	if (wheel) {
		m_fDistance -= (wheel * m_fRate);

		if (m_fDistance > 100) {
			m_fDistance = 100;
		}

		if (m_fDistance < 1) {
			m_fDistance = 1;
		}
	}

	calcEyePos();
}

void CCamera::calcEyePos()
{
	m_vEye.x = m_vLookat.x + sin(m_fLongitude)*cos(m_fLatitude)*m_fDistance;
	m_vEye.y = m_vLookat.y + sin(m_fLatitude)*m_fDistance;
	m_vEye.z = m_vLookat.z + cos(m_fLongitude)*cos(m_fLatitude)*m_fDistance;
}

void CCamera::render()
{
	//视图变换矩阵
	D3DXMatrixLookAtLH(&m_mMatView, &m_vEye, &m_vLookat, &m_vUp);
	//视图变换
	m_pDevice->SetTransform(D3DTS_VIEW, &m_mMatView);

	//投影变换矩阵
	D3DXMatrixPerspectiveFovLH(&m_mProject, m_fAngle, m_fAspectRatio, m_fNearZ, m_fFarZ);
	//投影变换
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_mProject);
}