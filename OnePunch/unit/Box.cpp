#include "box.h"
#include "d3ddevice.h"
#include "input.h"
#include "camera.h"
#include "MainWnd.h"

CBox::CBox()
{
	D3DXMatrixIdentity(&m_mMatrix);//��λ��

	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.�����������
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, 
								".\\texture\\texture.png", &m_pTexture)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������ʧ��", "����", MB_OK);
		return;
	}

	//���㻺����
	if (FAILED(m_pDevice->CreateVertexBuffer(MAX_VERTEX_NUM * sizeof(vertexData), 
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "�������㻺����ʧ�ܣ�", "����", MB_OK);
		return;
	}

	vertexData data[MAX_VERTEX_NUM] = {
		//�� ��
		{ -1, 1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  0.0f,  0.0f},    //0
		{  1, 1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  1.0f,  0.0f},    //1
		{ -1,-1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  0.0f,  1.0f},    //2
		{  1,-1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  1.0f,  1.0f},    //3

		//ǰ ��
		{ -1, 1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  1.0f,  0.0f},  //4
		{  1, 1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  0.0f,  0.0f},  //5
		{ -1,-1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  1.0f,  1.0f},  //6
		{  1,-1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  0.0f,  1.0f},  //7

		//�� ��
		{ -1, 1, 1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  0.0f,  0.0f },   //8   0
		{ -1, 1,-1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  1.0f,  0.0f },   //9   4
		{ -1,-1, 1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  0.0f,  1.0f },   //10  2
		{ -1,-1,-1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  1.0f,  1.0f },   //11  6

		//�� ��
		{  1, 1, 1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  1.0f,  0.0f },   //12  1
		{  1, 1,-1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  0.0f,  0.0f },   //13  5
		{  1,-1, 1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  1.0f,  1.0f },   //14  3
		{  1,-1,-1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  0.0f,  1.0f },   //15  7

		//�� ��
		{ -1, 1, 1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  0.0f,  0.0f }, //16  0
		{ -1, 1,-1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  1.0f,  0.0f }, //17  4
		{  1, 1, 1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  0.0f,  1.0f }, //18  1
		{  1, 1,-1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  1.0f,  1.0f }, //19  5

		//�� ��
		{ -1,-1, 1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  0.0f,  0.0f },//20 2
		{ -1,-1,-1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  1.0f,  0.0f },//21 6
		{  1,-1, 1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  0.0f,  1.0f },//22 3
		{  1,-1,-1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  1.0f,  1.0f },//23 7
	};

	//1.֪ͨD3D�豸 ��Ҫ�Զ��㻺���������ڴ����
	//2.ͬʱ���Ի�ȡ�����㻺�����д洢�������ݵ�λ��ָ��
	void* pvd;
	m_pd3dvb->Lock(0, MAX_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, MAX_VERTEX_NUM * sizeof(vertexData));
	m_pd3dvb->Unlock();


	//1.��������������
	//2.�������������ڵ����ݸ�ֵ

	if (FAILED(m_pDevice->CreateIndexBuffer(36 * sizeof(int),
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������������ʧ��!","����", MB_OK);
		return;
	}

	int arr[] = {0,2,1,2,3,1,     //��
				 4,7,6,4,5,7,     //ǰ
				8,9,10,9,11,10,   //��
				13,12,14,15,13,14,//��
				16,18,19,16,19,17,//��
				20,21,23,20,23,22,//��
				};
	int* pIndex;
	m_pd3dib->Lock(0,36*sizeof(int), (void**)&pIndex, 0);
	memcpy(pIndex, arr, sizeof(arr));
	m_pd3dib->Unlock();
}

CBox::~CBox()
{
}

void CBox::render()
{
	//��ʼ����
	m_pDevice->BeginScene();

	//��������
	m_pDevice->SetTexture(0, m_pTexture);
	//����������Ⱦ״̬
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//������˵ķ�ʽ
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//�������Թ���
	D3DCAPS9 caps;
	m_pDevice->GetDeviceCaps(&caps);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	//���û�����Դ��
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//�������������ʽ
	m_pDevice->SetFVF(VERTEX_FVF);
	//���õ�ǰʹ�õ�����������
	m_pDevice->SetIndices(m_pd3dib);

	//����ͼԪ
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MAX_VERTEX_NUM, 0, 12);

	m_pDevice->SetTexture(0, NULL);
	m_pDevice->EndScene();
}

void CBox::release()
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

	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}