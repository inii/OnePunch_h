#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

//公告板
class CBillBoard : public CNode
{
	struct vertexData
	{
		float x, y, z;
		DWORD color;
		float u1, v1;
	};
	DWORD VERTEX_FVF;//灵活顶点格式

#define BILL_MAX_VERTEX_NUM 4

	CBillBoard(const std::string& path);
public:
	~CBillBoard();

	static CBillBoard* create(const std::string& path) {
		CBillBoard* map = new CBillBoard(path);
		return map;
	}

	void render();
	void update(float dt);
	void release();

private:

	LPDIRECT3DDEVICE9		m_pDevice;//d3d设备
	IDirect3DVertexBuffer9* m_pd3dvb; //顶点缓冲区
	IDirect3DIndexBuffer9*  m_pd3dib; //索引缓冲区
	LPDIRECT3DTEXTURE9		m_pTexture;//纹理1
};

