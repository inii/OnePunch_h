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

	//1.�����������
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, 
								".\\texture\\sand.bmp", &m_pTexture1)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������ʧ��", "����", MB_OK);
		return;
	}

	//1.�����������
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice,
								".\\texture\\map_texture.jpg", &m_pTexture2)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������ʧ��", "����", MB_OK);
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
	//���㻺����
	if (FAILED(m_pDevice->CreateVertexBuffer(buffsize,
		0,VERTEX_FVF, D3DPOOL_DEFAULT, &m_pd3dvb, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "�������㻺����ʧ�ܣ�", "����", MB_OK);
		return;
	}

	//1.֪ͨD3D�豸 ��Ҫ�Զ��㻺���������ڴ����
	//2.ͬʱ���Ի�ȡ�����㻺�����д洢�������ݵ�λ��ָ��
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

	//1.��������������
	//2.�������������ڵ����ݸ�ֵ
	buffsize = width * 2 * 3 * sizeof(int) * height;
	if (FAILED(m_pDevice->CreateIndexBuffer(buffsize,
		0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pd3dib, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "��������������ʧ��!","����", MB_OK);
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

//��ȡ�߶�ͼ�ĸ߶�
float CTerrain::getHight(float x, float z)
{
	x = x + width / 2.0f;
	z = z + height / 2.0f;

	int ix = x;
	int iz = z;

	float fOffsetX = x - ix;  // offset ƫ��
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

	//��ʼ����
	m_pDevice->BeginScene();
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	m_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	m_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	m_pDevice->SetTexture(0, m_pTexture1);
	//������˵ķ�ʽ
	m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//����Ѱַ
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	////�������Թ���
	//D3DCAPS9 caps;
	//m_pDevice->GetDeviceCaps(&caps);
	//m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, caps.MaxAnisotropy);

	m_pDevice->SetTexture(1, m_pTexture2);
	//����������Ⱦ״̬ ��������Ⱦ����
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	m_pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);

	//������˵ķ�ʽ
	m_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//����Ѱַ
	m_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pDevice->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//���û�����Դ��
	m_pDevice->SetStreamSource(0, m_pd3dvb, 0, sizeof(vertexData));
	//�������������ʽ
	m_pDevice->SetFVF(VERTEX_FVF);
	//���õ�ǰʹ�õ�����������
	m_pDevice->SetIndices(m_pd3dib);

	//����ͼԪ
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (width + 1)*(height + 1), 0, width*height * 2);

	//�ָ�Ĭ��
	m_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTA_TEXTURE);
	m_pDevice->SetTexture(0, NULL);
	m_pDevice->SetTexture(1, NULL);

	m_pDevice->EndScene();
}

//��ȡ����λ��
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
			sprintf(str, "�������ͼ����:%.2f,%.2f,%.2f\n", vPos.x, vPos.y, vPos.z);
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

//�����
bool CTerrain::mousePick(D3DXVECTOR3& vPos)
{
	//��ȡ��Ļ�ϵĵ������
	POINT pt = CMainWnd::getInstance().getCursorPos();
	char str[255];
	sprintf(str, "�������Ļ����:%d,%d\n", pt.x, pt.y);
	OutputDebugString(str);

	//��ȡ���߷���
	D3DXVECTOR3 vRayDir;
	if(!CalculateRayDir(pt, vRayDir)) return false;

	//��ȡ������� �����۾������������
	D3DXVECTOR3 vRayPos = CCamera::getInstance().getEyePos();

	//�������߲ο���
	CLine* line = (CLine*)CGameApp::getInstance().getRoot3d()->getChildByName("line");
	if(line)
		line->setVertexPos(vRayPos, vRayPos+10*vRayDir);

	D3DXMATRIX mat;
	D3DXMatrixInverse(&mat, NULL, &m_mMatrix);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &mat);//����ı任
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &mat);//λ�õı任

	float fDis = FLT_MAX;//��󸡵���
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
		D3DXVec3TransformCoord(&vPos, &vPos, &m_mMatrix);//λ�õı任
		return true;
	}
	return false;
}

// ����ѡ�����������������귽��
bool CTerrain::CalculateRayDir(POINT pt, D3DXVECTOR3& vDir)
{
	CCmdLine& line = CCmdLine::getInstance();
	int w = line.getScreenW();
	int h = line.getScreenH();

	if (pt.x < 0 || pt.y < 0 || pt.x > w || pt.y > h)
		return false;

	// ��ȡ�Կ��豸��Ϣ
	D3DVIEWPORT9 t_vp;
	m_pDevice->GetViewport(&t_vp);

	// ��ȡͶӰ����
	D3DXMATRIX t_mProj;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &t_mProj);

	// ������ͼ���������������������
	D3DXVECTOR3 vRayDir;
	vRayDir.x = (((2.0f * pt.x) / t_vp.Width) - 1.0f) / t_mProj._11;
	vRayDir.y = (((-2.0f * pt.y) / t_vp.Height) + 1.0f) / t_mProj._22;
	vRayDir.z = 1.0f; //�̶�Ϊ1 ���ܽ�ƽ���λ��

	D3DXVec3Normalize(&vRayDir, &vRayDir);

	// �Ѽ�������ķ���任Ϊ��������
	D3DXMATRIX t_mView;

	m_pDevice->GetTransform(D3DTS_VIEW, &t_mView);
	D3DXMatrixInverse(&t_mView, NULL, &t_mView);
	D3DXVec3TransformNormal(&vDir, &vRayDir, &t_mView);
	D3DXVec3Normalize(&vDir, &vDir);

	return true;
}