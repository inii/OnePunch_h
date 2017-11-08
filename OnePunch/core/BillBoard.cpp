#include "billboard.h"
#include "d3ddevice.h"
#include "input.h"
#include "camera.h"
#include "GameApp.h"
#include "Terrain.h"
#include "MainWnd.h"

CBillBoard::CBillBoard(const std::string& path)
{
	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, path.c_str(), &m_pTexture)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}

	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(BILL_MAX_VERTEX_NUM * sizeof(vertexData),
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	vertexData data[BILL_MAX_VERTEX_NUM] = {
		{ -1,  1,  0, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 0.0f },   //0
		{  1,  1,  0, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0.0f },   //1
		{ -1, -1,  0, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 1.0f },   //2
		{  1, -1,  0, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 1.0f },   //3
	};

	//1.通知D3D设备 将要对顶点缓冲区进行内存操作
	//2.同时可以获取到顶点缓冲区中存储顶点数据的位置指针
	void* pvd;
	m_pd3dvb->Lock(0, BILL_MAX_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, BILL_MAX_VERTEX_NUM * sizeof(vertexData));
	m_pd3dvb->Unlock();

	//1.创建索引缓冲区
	//2.给索引缓冲区内的数据赋值
	if (FAILED(m_pDevice->CreateIndexBuffer(6 * sizeof(int),
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建索引缓冲区失败!","警告", MB_OK);
		return;
	}

	int arr[] = {0,1,2,
				 2,1,3};
	int* pIndex;
	m_pd3dib->Lock(0,6*sizeof(int), (void**)&pIndex, 0);
	memcpy(pIndex, arr, sizeof(arr));
	m_pd3dib->Unlock();
}

CBillBoard::~CBillBoard()
{
}

void CBillBoard::render()
{
	//开始绘制
	m_pDevice->BeginScene();
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	//设置纹理
	m_pDevice->SetTexture(0, m_pTexture);

	//设置纹理渲染状态
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	//纹理过滤的方式
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//alpha测试
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//测试参考值
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x3F);
	//测试函数
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//设置绘制资源流
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//设置流的灵活顶点格式
	m_pDevice->SetFVF(VERTEX_FVF);
	//设置当前使用的索引缓冲区
	m_pDevice->SetIndices(m_pd3dib);

	//绘制图元
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, BILL_MAX_VERTEX_NUM, 0, 2);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pDevice->SetTexture(0, NULL);

	m_pDevice->EndScene();

	CNode::render();
}

void CBillBoard::update(float dt)
{
	CNode::update(dt);

	D3DXMATRIX rotate;
	D3DXMatrixIdentity(&rotate);

	D3DXMATRIX mat = CCamera::getInstance().getViewMatrix();

	rotate._11 = mat._11;
	rotate._13 = mat._13;
	rotate._31 = mat._31;
	rotate._33 = mat._33;

	D3DXMatrixInverse(&rotate, NULL, &rotate);

	//begin 这些逻辑代码应该放到公告板树的逻辑中去 暂时放这里
	CNode* pRoot = CGameApp::getInstance().getRoot3d();
	CTerrain* p = (CTerrain*)pRoot->getChildByName("map");
	float h = 0.0f;
	if(p)
		p->getHight(m_mMatrix._41, m_mMatrix._43);

	rotate._41 = m_mMatrix._41;
	rotate._42 = h+1;
	rotate._43 = m_mMatrix._43;
	//end

	m_mMatrix = rotate;
}

void CBillBoard::release()
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