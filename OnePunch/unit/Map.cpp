#include "map.h"
#include "d3ddevice.h"
#include "input.h"
#include "MainWnd.h"

CMap::CMap(const std::string& path)
{
	VERTEX_FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, "texture\\texture3.bmp", &m_pTexture1)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, "texture\\Community.jpg", &m_pTexture2)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}

	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(MAP_MAX_VERTEX_NUM * sizeof(vertexData),
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	vertexData data[MAP_MAX_VERTEX_NUM] = {
		{ 400,  600, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 0.0f, 0.0f, 0.0f },   //0
		{ 600,  600, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0.0f, 1.0f, 0.0f },   //1
		{ 400,  400, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 0.0f, 1.0f, 0.0f, 1.0f },   //2
		{ 600,  400, 0, 0.5, D3DCOLOR_ARGB(255,255,255,255), 1.0f, 1.0f, 1.0f, 1.0f },   //3
	};

	//1.通知D3D设备 将要对顶点缓冲区进行内存操作
	//2.同时可以获取到顶点缓冲区中存储顶点数据的位置指针
	void* pvd;
	m_pd3dvb->Lock(0, MAP_MAX_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, MAP_MAX_VERTEX_NUM * sizeof(vertexData));
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
	//开始绘制
	m_pDevice->BeginScene();

	//m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//m_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);

	//设置纹理渲染状态
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	//纹理过滤的方式
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	////current
	//m_pDevice->SetTexture(1, m_pTexture2);
	////设置纹理渲染状态 多纹理渲染设置
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

	////纹理过滤的方式
	//m_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//纹理寻址
	//m_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255,0,0));
	//m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////各向异性过滤
	//D3DCAPS9 caps;
	//m_pDevice->GetDeviceCaps(&caps);
	//m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	//m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////alpha测试
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xF0);
	//m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//设置绘制资源流
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//设置流的灵活顶点格式
	m_pDevice->SetFVF(VERTEX_FVF);
	//设置当前使用的索引缓冲区
	m_pDevice->SetIndices(m_pd3dib);

	//绘制图元
	//设置纹理
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