#pragma once
#include "Node.h"

class CLine : public CNode
{
	struct vertexData
	{
		float x, y, z;
		DWORD color;
	};
	DWORD VERTEX_FVF;//�����ʽ

#define LINE_VERTEX_NUM 2

	CLine();
public:
	~CLine();

	static CLine* create() {
		CLine* line = new CLine();
		return line;
	}

	//���ö���λ��
	void setVertexPos(const D3DXVECTOR3& v0, const D3DXVECTOR3& v1);

	void render();
	void update(float dt);
	void release();

private:

	LPDIRECT3DDEVICE9		m_pDevice;//d3d�豸
	IDirect3DVertexBuffer9* m_pd3dvb; //���㻺����
};

