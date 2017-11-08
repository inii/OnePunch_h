#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

//������
class CTerrain : public CNode
{
	struct vertexData
	{
		float x, y, z;
		DWORD color;
		float u, v;
	};
	DWORD VERTEX_FVF;//�����ʽ

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

	//��ȡ�߶�ͼ�ĸ߶�
	float getHight(float x, float z);

	//��ȡ��ͼrect
	RECT getRect() { return{-width/2,-height/2,width/2,height/2}; }

private:
	//�����
	bool mousePick(D3DXVECTOR3& vPos);
	//�������߷���
	bool CalculateRayDir(POINT pt, D3DXVECTOR3& vDir);
	//��ȡ����λ��
	D3DXVECTOR3 getVertexPos(int w, int h);

	int width;
	int height;

	float fHeightOdds;

	DWORD *mMapData;

	LPDIRECT3DDEVICE9		m_pDevice;//d3d�豸
	IDirect3DVertexBuffer9* m_pd3dvb; //���㻺����
	IDirect3DIndexBuffer9*  m_pd3dib; //����������
	LPDIRECT3DTEXTURE9		m_pTexture1;//����1
	LPDIRECT3DTEXTURE9		m_pTexture2;//����2

	LPDIRECT3DTEXTURE9		m_pHightMap;//�߶�ͼ
};

