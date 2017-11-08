#include "map.h"
#include "d3ddevice.h"
#include "input.h"
#include "MainWnd.h"

CMap::CMap(const std::string& path)
{
	VERTEX_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.�����������
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, "texture\\texture3.bmp", &m_pTexture1)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������ʧ��", "����", MB_OK);
		return;
	}
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, "texture\\Community.jpg", &m_pTexture2)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������ʧ��", "����", MB_OK);
		return;
	}

	//���㻺����
	if (FAILED(m_pDevice->CreateVertexBuffer(MAP_MAX_VERTEX_NUM * sizeof(vertexData),
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "�������㻺����ʧ�ܣ�", "����", MB_OK);
		return;
	}

	vertexData data[MAP_MAX_VERTEX_NUM] = {
		{ 400,  600, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 0.0f, 0.0f, 0.0f },   //0
		{ 600,  600, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0.0f, 1.0f, 0.0f },   //1
		{ 400,  400, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 1.0f, 0.0f, 1.0f },   //2
		{ 600,  400, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 1.0f, 1.0f, 1.0f },   //3
	};

	//1.֪ͨD3D�豸 ��Ҫ�Զ��㻺���������ڴ����
	//2.ͬʱ���Ի�ȡ�����㻺�����д洢�������ݵ�λ��ָ��
	void* pvd;
	m_pd3dvb->Lock(0, MAP_MAX_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, MAP_MAX_VERTEX_NUM * sizeof(vertexData));
	m_pd3dvb->Unlock();

	//1.��������������
	//2.�������������ڵ����ݸ�ֵ
	if (FAILED(m_pDevice->CreateIndexBuffer(6 * sizeof(int),
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������������ʧ��!","����", MB_OK);
		return;
	}

	int arr[] = {0,2,1,
				 1,2,3};
	int* pIndex;
	m_pd3dib->Lock(0,6*sizeof(int), (void**)&pIndex, 0);
	memcpy(pIndex, arr, sizeof(arr));
	m_pd3dib->Unlock();
}

CMap::~CMap()
{
}

void CMap::render()
{
	//��ʼ����
	m_pDevice->BeginScene();

	//m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//m_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

	//����������Ⱦ״̬
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	//������˵ķ�ʽ
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////current
	//m_pDevice->SetTexture(1, m_pTexture2);
	////����������Ⱦ״̬ ��������Ⱦ����
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

	////������˵ķ�ʽ
	//m_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//����Ѱַ
	//m_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255,0,0));
	//m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////�������Թ���
	//D3DCAPS9 caps;
	//m_pDevice->GetDeviceCaps(&caps);
	//m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////alpha����
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xF0);
	//m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���û�����Դ��
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//�������������ʽ
	m_pDevice->SetFVF(VERTEX_FVF);
	//���õ�ǰʹ�õ�����������
	m_pDevice->SetIndices(m_pd3dib);

	//����ͼԪ
	//��������
	m_pDevice->SetTexture(0, m_pTexture1);

	//m_pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MAP_MAX_VERTEX_NUM, 0, 2);

	//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pDevice->SetTexture(0, NULL);
	//m_pDevice->SetTexture(1, NULL);

	m_pDevice->EndScene();

	CNode::render();
}

void CMap::update(float dt)
{
	CNode::update(dt);
}

void CMap::release()
{
	if (m_pd3dvb)
	{
		m_pd3dvb->Release();
		m_pd3dvb = NULL;
	}

	if (m_pd3dib)
	{
		m_pd3dib->Release();
		m_pd3dib = NULL;
	}

	if (m_pTexture1)
	{
		m_pTexture1->Release();
		m_pTexture1 = NULL;
	}
}