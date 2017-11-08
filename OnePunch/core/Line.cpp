#include "Line.h"
#include "d3ddevice.h"
#include "MainWnd.h"

CLine::CLine()
{
	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//���㻺����
	if (FAILED(m_pDevice->CreateVertexBuffer(LINE_VERTEX_NUM * sizeof(vertexData),
		0, VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "�������㻺����ʧ�ܣ�", "����", MB_OK);
		return;
	}

	vertexData data[LINE_VERTEX_NUM] = {
		{ -1,   0,   1, D3DCOLOR_ARGB(255,255,255,255) },   //0
		{  1,   0,   1, D3DCOLOR_ARGB(255,255,0,0) },   //1
	};

	//1.֪ͨD3D�豸 ��Ҫ�Զ��㻺���������ڴ����
	//2.ͬʱ���Ի�ȡ�����㻺�����д洢�������ݵ�λ��ָ��
	void* pvd;
	m_pd3dvb->Lock(0, LINE_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, LINE_VERTEX_NUM * sizeof(vertexData));
	m_pd3dvb->Unlock();
}

CLine::~CLine()
{
}

void CLine::setVertexPos(const D3DXVECTOR3& v0, const D3DXVECTOR3& v1)
{
	vertexData* pvd;
	m_pd3dvb->Lock(0, LINE_VERTEX_NUM * sizeof(vertexData), (void**)&pvd, 0);
	pvd[0].x = v0.x;
	pvd[0].y = v0.y;
	pvd[0].z = v0.z;

	pvd[1].x = v1.x;
	pvd[1].y = v1.y;
	pvd[1].z = v1.z;

	m_pd3dvb->Unlock();
}

void CLine::render()
{
	//��ʼ����
	m_pDevice->BeginScene();

	//���û�����Դ��
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//�������������ʽ
	m_pDevice->SetFVF(VERTEX_FVF);

	m_pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);
	m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	m_pDevice->EndScene();

	CNode::render();
}

void CLine::update(float dt)
{
	CNode::update(dt);
}

void CLine::release()
{
	if (m_pd3dvb)
	{
		m_pd3dvb->Release();
		m_pd3dvb = NULL;
	}
}