#include "terrain.h"
#include "d3ddevice.h"
#include "input.h"
#include "MainWnd.h"
#include "CmdLine.h"
#include "Camera.h"
#include "GameApp.h"
#include "Line.h"
#include "TextureCache.h"

CTerrain::CTerrain():
fHeightOdds(0.05f)
{
	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, 
								".\\texture\\sand.bmp", &m_pTexture1)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice,
								".\\texture\\map_texture.jpg", &m_pTexture2)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "加载纹理失败", "警告", MB_OK);
		return;
	}

	CTexture* p = CTextureCache::getInstance().createTexture(".\\texture\\Terrain.jpg");
	m_pHightMap = p->getD3dTex();

	width = p->getWidth() - 1;
	height = p->getHeight() - 1;

	D3DLOCKED_RECT lockedrect;
	m_pHightMap->LockRect(0, &lockedrect, NULL, 0);
	DWORD* pBits = (DWORD*)lockedrect.pBits;

	mMapData = new DWORD[(width+1)*(height+1)];
	memcpy(mMapData, pBits, (width + 1)*(height + 1)*sizeof(DWORD));
	//for (int h = 0; h < height + 1; h++) {
	//	for (int w = 0; w < width + 1; w++) {
	//		mMapData[h*(width + 1) + w] = pBits[h*(width + 1) + w];
	//	}
	//}

	int buffsize = (width + 1)*(height + 1) * sizeof(vertexData);
	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(buffsize,
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	//1.通知D3D设备 将要对顶点缓冲区进行内存操作
	//2.同时可以获取到顶点缓冲区中存储顶点数据的位置指针
	vertexData* pvd;
	m_pd3dvb->Lock(0, buffsize, (void**)&pvd, 0);

	for (int h = 0; h < height+1; h++) {
		for (int w = 0; w < width+1; w++) {
			pvd[h*(width + 1) + w].x = w-width/2.0f;
			pvd[h*(width + 1) + w].y = (mMapData[h*(width + 1) + w] & 0xff)*fHeightOdds;
			pvd[h*(width + 1) + w].z = h-height/2.0f;

			BYTE b = (mMapData[h*(width + 1) + w] & 0xff00) >> 8;
			if(b != 0)
				pvd[h*(width + 1) + w].color = D3DCOLOR_ARGB(255, 255, 255, 255);
			else
				pvd[h*(width + 1) + w].color = D3DCOLOR_ARGB(0, 255, 255, 255);

			pvd[h*(width + 1) + w].v = w/(float)width *16;
			pvd[h*(width + 1) + w].u = h/(float)height*16;
		}
	}

	m_pd3dvb->Unlock();
	m_pHightMap->UnlockRect(0);

	//1.创建索引缓冲区
	//2.给索引缓冲区内的数据赋值
	buffsize = width * 2 * 3 * sizeof(int) * height;
	if (FAILED(m_pDevice->CreateIndexBuffer(buffsize,
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "创建索引缓冲区失败!","警告", MB_OK);
		return;
	}

	int* pIndex;
	m_pd3dib->Lock(0, buffsize, (void**)&pIndex, 0);

	int colIndexSize = width*2*3;
	int rectIndexSize = 6;

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			pIndex[colIndexSize*h + w*rectIndexSize + 0] = h*(width + 1) + w;  // 0
			pIndex[colIndexSize*h + w*rectIndexSize + 1] = h*(width + 1) + w + (width + 1); //3
			pIndex[colIndexSize*h + w*rectIndexSize + 2] = h*(width + 1) + w + 1;//1

			pIndex[colIndexSize*h + w*rectIndexSize + 3] = h*(width + 1) + w + 1;//1
			pIndex[colIndexSize*h + w*rectIndexSize + 4] = h*(width + 1) + w + (width + 1); //3
			pIndex[colIndexSize*h + w*rectIndexSize + 5] = h*(width + 1) + w + (width + 1) + 1;//4
		}
	}

	m_pd3dib->Unlock();
}

CTerrain::~CTerrain()
{
}

//获取高度图的高度
float CTerrain::getHight(float x, float z)
{
	x = x + width / 2.0f;
	z = z + height / 2.0f;

	int ix = x;
	int iz = z;

	float fOffsetX = x - ix;  // offset 偏移
	float fOffsetZ = z - iz;

	float t0, t1, t2;
	if (fOffsetX + fOffsetZ > 1){
		fOffsetX = 1 - fOffsetX;
		fOffsetZ = 1 - fOffsetZ;

		t0 = (mMapData[(iz + 1)*(width + 1) + ix + 1] & 0xff)*fHeightOdds;
		t1 = (mMapData[iz*(width + 1) + ix + 1] & 0xff)*fHeightOdds;
		t2 = (mMapData[(iz + 1)*(width + 1) + ix] & 0xff)*fHeightOdds;
		return t0 + fOffsetX*(t2 - t0) + fOffsetZ * (t1 - t0);
	}
	else {
		t0 = (mMapData[iz*(width + 1) + ix] & 0xff)*fHeightOdds;
		t1 = (mMapData[(iz + 1)*(width + 1) + ix] & 0xff)*fHeightOdds;
		t2 = (mMapData[iz*(width + 1) + ix + 1] & 0xff)*fHeightOdds;
		return t0 + fOffsetX*(t2 - t0) + fOffsetZ * (t1 - t0);
	}
}

void CTerrain::render()
{
	CNode::render();

	//开始绘制
	m_pDevice->BeginScene();
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	m_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	m_pDevice->SetTexture(0, m_pTexture1);
	//纹理过滤的方式
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//纹理寻址
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////各向异性过滤
	//D3DCAPS9 caps;
	//m_pDevice->GetDeviceCaps(&caps);
	//m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	m_pDevice->SetTexture(1, m_pTexture2);
	//设置纹理渲染状态 多纹理渲染设置
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	//纹理过滤的方式
	m_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//纹理寻址
	m_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//设置绘制资源流
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//设置流的灵活顶点格式
	m_pDevice->SetFVF(VERTEX_FVF);
	//设置当前使用的索引缓冲区
	m_pDevice->SetIndices(m_pd3dib);

	//绘制图元
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (width + 1)*(height + 1), 0, width*height * 2);

	//恢复默认
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTA_TEXTURE);
	m_pDevice->SetTexture(0, NULL);
	m_pDevice->SetTexture(1, NULL);

	m_pDevice->EndScene();
}

//获取顶点位置
D3DXVECTOR3 CTerrain::getVertexPos(int w, int h)
{
	D3DXVECTOR3 v;
	v.x = w - width / 2.0f;
	v.y = (mMapData[h*(width + 1) + w] & 0xff)*fHeightOdds;
	v.z = h - height / 2.0f;

	return v;
}

void CTerrain::update(float dt)
{
	CNode::update(dt);

	if (CInput::getInstance().mouseDown(DIM_LBUTTON))
	{
		D3DXVECTOR3 vPos;
		if (mousePick(vPos)) {
			char str[255];
			sprintf(str, "点击到地图坐标:%.2f,%.2f,%.2f\n", vPos.x, vPos.y, vPos.z);
			OutputDebugString(str);
		}
	}
}

void CTerrain::release()
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

	if (m_pTexture2)
	{
		m_pTexture2->Release();
		m_pTexture2 = NULL;
	}

	delete [] mMapData;
}

//鼠标点击
bool CTerrain::mousePick(D3DXVECTOR3& vPos)
{
	//获取屏幕上的点的坐标
	POINT pt = CMainWnd::getInstance().getCursorPos();
	char str[255];
	sprintf(str, "点击到屏幕坐标:%d,%d\n", pt.x, pt.y);
	OutputDebugString(str);

	//获取射线方向
	D3DXVECTOR3 vRayDir;
	if(!CalculateRayDir(pt, vRayDir)) return false;

	//获取射线起点 就是眼睛点的世界坐标
	D3DXVECTOR3 vRayPos = CCamera::getInstance().getEyePos();

	//绘制视线参考线
	CLine* line = (CLine*)CGameApp::getInstance().getRoot3d()->getChildByName("line");
	if(line)
		line->setVertexPos(vRayPos, vRayPos+10*vRayDir);

	D3DXMATRIX mat;
	D3DXMatrixInverse(&mat, NULL, &m_mMatrix);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &mat);//方向的变换
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &mat);//位置的变换

	float fDis = FLT_MAX;//最大浮点数
	bool bCorss = false;

	for (int h = 0; h < height;h++) {
		for (int w = 0; w < width;w++) {
			D3DXVECTOR3 v0, v1, v2;

			float dis = 0.0f;

			v0 = getVertexPos(w, h);  //0
			v1 = getVertexPos(w,h+1); //3
			v2 = getVertexPos(w+1, h);//1

			BOOL b = D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, NULL, NULL, &dis);
			if (b) {
				bCorss = true;
				if (dis < fDis)
					fDis = dis;
			}

			v0 = getVertexPos(w + 1, h);	//1
			v1 = getVertexPos(w, h + 1);	//3
			v2 = getVertexPos(w + 1, h + 1);//4

			b = D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, NULL, NULL, &dis);
			if (b) {
				bCorss = true;
				if (dis < fDis)
					fDis = dis;
			}
		}
	}

	if (bCorss) {
		vPos = vRayPos + fDis*vRayDir;
		D3DXVec3TransformCoord(&vPos, &vPos, &m_mMatrix);//位置的变换
		return true;
	}
	return false;
}

// 鼠标拣选，返回世界坐标的鼠标方向
bool CTerrain::CalculateRayDir(POINT pt, D3DXVECTOR3& vDir)
{
	CCmdLine& line = CCmdLine::getInstance();
	int w = line.getScreenW();
	int h = line.getScreenH();

	if (pt.x < 0 || pt.y < 0 || pt.x > w || pt.y > h)
		return false;

	// 获取显卡设备信息
	D3DVIEWPORT9 t_vp;
	m_pDevice->GetViewport(&t_vp);

	// 获取投影矩阵
	D3DXMATRIX t_mProj;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &t_mProj);

	// 基于视图坐标根据鼠标点击计算出方向
	D3DXVECTOR3 vRayDir;
	vRayDir.x = (((2.0f * pt.x) / t_vp.Width) - 1.0f) / t_mProj._11;
	vRayDir.y = (((-2.0f * pt.y) / t_vp.Height) + 1.0f) / t_mProj._22;
	vRayDir.z = 1.0f; //固定为1 不管近平面的位置

	D3DXVec3Normalize(&vRayDir, &vRayDir);

	// 把计算出来的方向变换为世界坐标
	D3DXMATRIX t_mView;

	m_pDevice->GetTransform(D3DTS_VIEW, &t_mView);
	D3DXMatrixInverse(&t_mView, NULL, &t_mView);
	D3DXVec3TransformNormal(&vDir, &vRayDir, &t_mView);
	D3DXVec3Normalize(&vDir, &vDir);

	return true;
}