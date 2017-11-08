#include "Line.h"
#include "d3ddevice.h"
#include "MainWnd.h"

CLine::CLine()
{
	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(LINE_VERTEX_NUM * sizeof(vertexData),
		0, VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	vertexData data[LINE_VERTEX_NUM] = {
		{ -1,   0,   1, D3DCOLOR_ARGB(255,255,255,255) },   //0
		{  1,   0,   1, D3DCOLOR_ARGB(255,255,0,0) },   //1
	};

	//1.通知D3D设备 将要对顶点缓冲区进行内存操作
	//2.同时可以获取到顶点缓冲区中存储顶点数据的位置指针
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
	//开始绘制
	m_pDevice->BeginScene();

	//设置绘制资源流
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//设置流的灵活顶点格式
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