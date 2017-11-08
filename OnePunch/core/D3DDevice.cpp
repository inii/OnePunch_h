#include "D3DDevice.h"
#include "MainWnd.h"

CD3DDevice::CD3DDevice()
{
	m_pD3d = NULL;
	m_pDevice = NULL;
}

CD3DDevice::~CD3DDevice()
{
	if (m_pDevice) {
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pD3d) {
		m_pD3d->Release();
		m_pD3d = NULL;
	}
}

HRESULT CD3DDevice::init()
{
	HWND hWnd = CMainWnd::getInstance().getMainWnd();
	//����d3d����
	m_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d == NULL)
	{
		MessageBox(hWnd, "����d3d����ʧ�ܣ���", "����", MB_OK);
		return S_FALSE;
	}

	//�ж�Ӳ�����Ƿ�֧��4�����
	BOOL isOpenMutisample = false;
	DWORD numq = 0;
	if (SUCCEEDED(m_pD3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, FALSE,
		D3DMULTISAMPLE_2_SAMPLES, &numq)))
	{
		isOpenMutisample = true;
	}

	//��ȡ�豸��ʾģʽ
	D3DDISPLAYMODE d3ddm;
	m_pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	if (isOpenMutisample)
		d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	//d3dpp.BackBufferWidth = 1280;
	//d3dpp.BackBufferHeight = 720;

	//����d3d�豸����
	HRESULT r = m_pD3d->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pDevice);
	if (FAILED(r))//SUCCEEDED
	{
		MessageBox(hWnd, "����d3d�豸ʧ�ܣ���", "����", MB_OK);
		return S_FALSE;
	}

	//D3DCAPS9 stCaps;
	//m_pDevice->GetDeviceCaps(&stCaps);
	//stCaps.MaxTextureBlendStages;

	//�����
	m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);

	//��
	m_pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_XRGB(128,128,128));

	float start = 20.0f;
	float end = 50;
	m_pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)&start);
	m_pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)&end);

	m_pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	//float desity = 0.1f;
	//m_pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)&desity);
	//m_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	D3DXCreateSprite(m_pDevice, &m_pSprite);

	return S_OK;
}
