#pragma once
#include "Node.h"

class CLine : public CNode
{
	struct vertexData
	{
		float x, y, z;
		DWORD color;
	};
	DWORD VERTEX_FVF;//灵活顶点格式

#define LINE_VERTEX_NUM 2

	CLine();
public:
	~CLine();

	static CLine* create() {
		CLine* line = new CLine();
		return line;
	}

	//设置顶点位置
	void setVertexPos(const D3DXVECTOR3& v0, const D3DXVECTOR3& v1);

	void render();
	void update(float dt);
	void release();

private:

	LPDIRECT3DDEVICE9		m_pDevice;//d3d设备
	IDirect3DVertexBuffer9* m_pd3dvb; //顶点缓冲区
};

