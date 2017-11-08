#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

//三角形
class CTerrain : public CNode
{
	struct vertexData
	{
		float x, y, z;
		DWORD color;
		float u, v;
	};
	DWORD VERTEX_FVF;//灵活顶点格式

	CTerrain();
public:
	~CTerrain();

	static CTerrain* create() {
		CTerrain* map = new CTerrain;
		return map;
	}

	void render();
	void update(float dt);
	void release();

	//获取高度图的高度
	float getHight(float x, float z);

	//获取地图rect
	RECT getRect() { return{-width/2,-height/2,width/2,height/2}; }

private:
	//鼠标点击
	bool mousePick(D3DXVECTOR3& vPos);
	//计算射线方向
	bool CalculateRayDir(POINT pt, D3DXVECTOR3& vDir);
	//获取顶点位置
	D3DXVECTOR3 getVertexPos(int w, int h);

	int width;
	int height;

	float fHeightOdds;

	DWORD *mMapData;

	LPDIRECT3DDEVICE9		m_pDevice;//d3d设备
	IDirect3DVertexBuffer9* m_pd3dvb; //顶点缓冲区
	IDirect3DIndexBuffer9*  m_pd3dib; //索引缓冲区
	LPDIRECT3DTEXTURE9		m_pTexture1;//纹理1
	LPDIRECT3DTEXTURE9		m_pTexture2;//纹理2

	LPDIRECT3DTEXTURE9		m_pHightMap;//高度图
};

