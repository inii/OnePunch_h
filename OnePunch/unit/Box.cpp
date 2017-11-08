#include "box.h"
#include "d3ddevice.h"
#include "input.h"
#include "camera.h"
#include "MainWnd.h"

CBox::CBox()
{
	D3DXMatrixIdentity(&m_mMatrix);//单位化

	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_NORMAL;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, 
								".\\texture\\texture.png", &m_pTexture)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}

	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(MAX_VERTEX_NUM * sizeof(vertexData), 
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	vertexData data[MAX_VERTEX_NUM] = {
		//后 粉
		{ -1, 1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  0.0f,  0.0f},    //0
		{  1, 1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  1.0f,  0.0f},    //1
		{ -1,-1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  0.0f,  1.0f},    //2
		{  1,-1, 1,   0,0,1, D3DCOLOR_XRGB(255,0,255),  1.0f,  1.0f},    //3

		//前 红
		{ -1, 1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  1.0f,  0.0f},  //4
		{  1, 1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  0.0f,  0.0f},  //5
		{ -1,-1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  1.0f,  1.0f},  //6
		{  1,-1,-1,  0,0,-1, D3DCOLOR_XRGB(255,0,0),  0.0f,  1.0f},  //7

		//左 蓝
		{ -1, 1, 1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  0.0f,  0.0f },   //8   0
		{ -1, 1,-1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  1.0f,  0.0f },   //9   4
		{ -1,-1, 1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  0.0f,  1.0f },   //10  2
		{ -1,-1,-1,  -1,0,0, D3DCOLOR_XRGB(0,0,255),  1.0f,  1.0f },   //11  6

		//右 绿
		{  1, 1, 1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  1.0f,  0.0f },   //12  1
		{  1, 1,-1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  0.0f,  0.0f },   //13  5
		{  1,-1, 1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  1.0f,  1.0f },   //14  3
		{  1,-1,-1,   1,0,0, D3DCOLOR_XRGB(0,255,0),  0.0f,  1.0f },   //15  7

		//上 黄
		{ -1, 1, 1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  0.0f,  0.0f }, //16  0
		{ -1, 1,-1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  1.0f,  0.0f }, //17  4
		{  1, 1, 1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  0.0f,  1.0f }, //18  1
		{  1, 1,-1,  0, 1,0, D3DCOLOR_XRGB(255,255,0),  1.0f,  1.0f }, //19  5

		//下 白
		{ -1,-1, 1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  0.0f,  0.0f },//20 2
		{ -1,-1,-1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  1.0f,  0.0f },//21 6
		{  1,-1, 1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  0.0f,  1.0f },//22 3
		{  1,-1,-1,  0,-1,0, D3DCOLOR_XRGB(255,255,255),  1.0f,  1.0f },//23 7
	};

	//1.通知D3D设备 将要对顶点缓冲区进行内存操作
	//2.同时可以获取到顶点缓冲区中存储顶点数据的位置指针
	void* pvd;
	m_pd3dvb->Lock(0, MAX_VERTEX_NUM * sizeof(vertexData), &pvd, 0);
	memcpy(pvd, data, MAX_VERTEX_NUM * sizeof(vertexData));
	m_pd3dvb->Unlock();


	//1.创建索引缓冲区
	//2.给索引缓冲区内的数据赋值

	if (FAILED(m_pDevice->CreateIndexBuffer(36 * sizeof(int),
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建索引缓冲区失败!","警告", MB_OK);
		return;
	}

	int arr[] = {0,2,1,2,3,1,     //后
				 4,7,6,4,5,7,     //前
				8,9,10,9,11,10,   //左
				13,12,14,15,13,14,//右
				16,18,19,16,19,17,//上
				20,21,23,20,23,22,//下
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
	//开始绘制
	m_pDevice->BeginScene();

	//设置纹理
	m_pDevice->SetTexture(0, m_pTexture);
	//设置纹理渲染状态
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//纹理过滤的方式
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//各向异性过滤
	D3DCAPS9 caps;
	m_pDevice->GetDeviceCaps(&caps);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	//设置绘制资源流
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//设置流的灵活顶点格式
	m_pDevice->SetFVF(VERTEX_FVF);
	//设置当前使用的索引缓冲区
	m_pDevice->SetIndices(m_pd3dib);

	//绘制图元
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