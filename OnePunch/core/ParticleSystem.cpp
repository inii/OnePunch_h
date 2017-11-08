#include "ParticleSystem.h"
#include "d3ddevice.h"
#include "Input.h"
#include "MainWnd.h"
#include "Camera.h"

CParticleSystem::CParticleSystem()
{
	init();
}

CParticleSystem::~CParticleSystem()
{
}

D3DXVECTOR3 CParticleSystem::culcPos0()
{
	//球面发生器
	//vPos0.x = rand() % 100-50;
	//vPos0.y = rand() % 100-50;
	//vPos0.z = rand() % 100-50;
	//D3DXVec3Normalize(&vPos0, &vPos0);

	//茶壶发生器
	//vetrexNode* p = NULL;
	//mpMesh->LockVertexBuffer(0, (void**)&p);
	//DWORD num = mpMesh->GetNumVertices();

	//int r = rand() % num;
	//vPos0 = D3DXVECTOR3((p+r)->x, (p + r)->y, (p + r)->z);
	//mpMesh->UnlockVertexBuffer();

	//正方形发生器
	vPos0.x = rand() % 20 - 10;
	vPos0.y = 0;
	vPos0.z = rand() % 20 - 10;

	auto v = CCamera::getInstance().getEyePos();
	m_mMatrix._41 = v.x;
	m_mMatrix._42 = v.y+5.0f;
	m_mMatrix._43 = v.z;

	D3DXVec3TransformCoord(&vPos0, &vPos0, &m_mMatrix);

	return vPos0;
}

//增加一个粒子
void CParticleSystem::add()
{
	if (mLives.size() >= nMaxNum) {
		return;
	}

	if (mDeads.size() > 0) {
		Particle* p = mDeads.back();
		mDeads.pop_back();

		p->vPos = culcPos0();
		//vSpeed0.x = rand() % 20 - 10;
		//vSpeed0.y = rand() % 20 - 10;
		//vSpeed0.z = rand() % 20 - 10;
		p->vSpeed = vSpeed0;
		p->fKeepTime = 0;
		p->curRGB = D3DCOLOR_ARGB(255, rand() % 255, rand() % 255, rand() % 255);
		mLives.push_back(p);
	}
	else {
		Particle* p = new Particle();
		p->vPos = culcPos0();
		//vSpeed0.x = rand() % 20 - 10;
		//vSpeed0.y = rand() % 20 - 10;
		//vSpeed0.z = rand() % 20 - 10;
		p->vSpeed = vSpeed0;
		p->fKeepTime = 0;
		p->curRGB = D3DCOLOR_ARGB(255, rand()%255, rand()%255, rand()%255);
		mLives.push_back(p);
	}
}

//释放
void CParticleSystem::release()
{

}

//初始化
void CParticleSystem::init()
{
	nMaxNum = 800;
	mBufferSize = 20;
	mLiveTime = 2.0f;

	vPos0 = D3DXVECTOR3(0,0,0);
	vSpeed0 = D3DXVECTOR3(0,0,0);

	vGravityAddSpeed = D3DXVECTOR3(0.0f,-9.8f,0.0f);

	VERTEX_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	m_pDevice = CD3DDevice::getInstance().getDevice();

	//1.加载纹理对象
	if (FAILED(D3DXCreateTextureFromFile(m_pDevice, "texture\\particle1.jpg", &m_pTexture)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "粒子系统：加载纹理失败", "警告", MB_OK);
		return;
	}

	//顶点缓冲区
	if (FAILED(m_pDevice->CreateVertexBuffer(mBufferSize * sizeof(vertexData),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY, VERTEX_FVF, D3DPOOL_DEFAULT, &m_pVB, 0)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "粒子系统:创建顶点缓冲区失败！", "警告", MB_OK);
		return;
	}

	LPD3DXBUFFER sphBuff;
	D3DXCreateTeapot(m_pDevice, &mpMesh, &sphBuff);
	//D3DXCreateCylinder(m_pDevice, 2, 0, 5, 25, 15, &mpMesh, &sphBuff);
}

//更新
void CParticleSystem::update(float dt)
{
	CNode::update(dt);

	CInput& input = CInput::getInstance();

	//if(input.keyHold(DIK_T)){
		for (int i=0;i<4;i++)
			add();
	//}

	for (auto it = mLives.begin(); it != mLives.end();)
	{
		Particle* p = *it;

		p->vPos += p->vSpeed*dt;
		p->vSpeed += vGravityAddSpeed*dt;
		p->fKeepTime += dt;

		DWORD c = p->curRGB;
		byte alpha = (mLiveTime - p->fKeepTime) / mLiveTime * 255;

		c = (c & 0x00ffffff) | (alpha << 24);
		p->curRGB = c;

		if (p->fKeepTime >= mLiveTime)
		{
			mDeads.push_back(p);

			it = mLives.erase(it);
			continue;
		}
		it++;
	}
}

DWORD FtoW(float w)
{
	return (*(DWORD*)&w);
}

//渲染
void CParticleSystem::render()
{
	CNode::render();

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	m_pDevice->SetTransform(D3DTS_WORLD, &mat);

	//关闭深度缓冲写入  深度测试返回true 只改颜色 不改深度
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//关闭灯光
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//设置alpha混合
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DTOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 纹理颜色跟顶点颜色混合
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//设置点精灵 point sprite enable
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_POINTSIZE,    FtoW(0.5f));
	m_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN,FtoW(0.0f));
	//float size = sqrt(1/(a + b*d + c*(d*d)));//d表示点离摄像机距离
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoW(0.0f)); //固定大小
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoW(0.0f)); //线性变化
	m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoW(1.0f)); //指数变化

	//设置顶点资源
	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(vertexData));
	m_pDevice->SetFVF(VERTEX_FVF);

	//设置纹理
	m_pDevice->SetTexture(0, m_pTexture);

	int remainNum = mLives.size(); // 剩余渲染个数

	auto it = mLives.begin();
	do
	{
		int curRenderNum = mBufferSize; //该次渲染个数
		if (mBufferSize >= remainNum) {
			curRenderNum = remainNum;
		}

		if (curRenderNum == 0)
			break;

		int index = mLives.size()-remainNum;
		vertexData* pData;
		m_pVB->Lock(0, curRenderNum*sizeof(vertexData), (void**)&pData, 0);

		int count = 0;
		while (count != curRenderNum)
		{
			pData[count].x = (*it)->vPos.x;
			pData[count].y = (*it)->vPos.y;
			pData[count].z = (*it)->vPos.z;

			pData[count].color = (*it)->curRGB;

			it++;
			count++;
		}
		//for (int i = 0; i < curRenderNum;i++) {
		//	pData[i].x = mLives[index + i]->vPos.x;
		//	pData[i].y = mLives[index + i]->vPos.y;
		//	pData[i].z = mLives[index + i]->vPos.z;

		//	pData[i].color = mLives[index + i]->curRGB;
		//}

		m_pVB->Unlock();
		m_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, curRenderNum);

		remainNum -= curRenderNum;

	} while (remainNum > 0);

	m_pDevice->SetTexture(0, NULL);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
}
