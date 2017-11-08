#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

//������
class CMap : public CNode
{
	struct vertexData
	{
		float x, y, z, rhw;
		DWORD color;
		float u1, v1;
		float u2, v2;
	};
	DWORD VERTEX_FVF;//�����ʽ

#define MAP_MAX_VERTEX_NUM 4

	CMap(const std::string& path);
public:
	~CMap();

	static CMap* create(const std::string& path) {
		CMap* map = new CMap(path);
		return map;
	}

	void render();
	void update(float dt);
	void release();

private:

	LPDIRECT3DDEVICE9		m_pDevice;//d3d�豸
	IDirect3DVertexBuffer9* m_pd3dvb; //���㻺����
	IDirect3DIndexBuffer9*  m_pd3dib; //����������
	LPDIRECT3DTEXTURE9		m_pTexture1;//����1
	LPDIRECT3DTEXTURE9		m_pTexture2;//����2
};

