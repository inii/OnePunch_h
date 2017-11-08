#pragma once
#include <list>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

using namespace std;
//粒子系统
class CParticleSystem : public CNode
{
	D3DXVECTOR3 vPos0;  //初始位置  -->发射点  -->发射器
	D3DXVECTOR3 vSpeed0;//初始速度
	D3DXVECTOR3 vGravityAddSpeed;//重力加速度
	float mLiveTime; //生存周期

	struct Particle
	{
		D3DXVECTOR3 vPos;		//位置
		D3DXVECTOR3 vSpeed;		//速度

		float		fKeepTime;	//持续时间
		D3DCOLOR	curRGB;		//当前颜色
	};

	struct vertexData
	{
		float x, y, z;
		DWORD color;
	};
	DWORD VERTEX_FVF;//灵活顶点格式


	struct vetrexNode {
		float x, y, z;
		float nx, ny, nz;
	};

public:
	CParticleSystem();
	~CParticleSystem();

	//增加一个粒子
	void add();
	//释放
	void release();
	//初始化
	void init();
	//更新
	void update(float dt);
	//渲染
	void render();

private:

	//计算初始位置
	D3DXVECTOR3 culcPos0();

	int nMaxNum; //最大粒子数

	ID3DXMesh* mpMesh;

	list<Particle*> mDeads; //消亡链表
	list<Particle*> mLives; //活动链表

	int mBufferSize;	//缓冲区大小

	LPDIRECT3DDEVICE9		m_pDevice;//d3d设备
	LPDIRECT3DTEXTURE9		m_pTexture;//纹理1
	IDirect3DVertexBuffer9* m_pVB;    //顶点缓冲区
};

