#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

//������
class CBox
{
	struct vertexData
	{
		float x, y, z;
		float nx, ny, nz;
		DWORD color;
		float u, v;
	};
	DWORD VERTEX_FVF;//�����ʽ

#define MAX_VERTEX_NUM 24
	CBox();
public:

	D3DXVECTOR3 pos;

	~CBox();

	static CBox* create() {
		CBox* box = new CBox();
		return box;
	}

	void render();
	void release();

	void setMatrix(const D3DXMATRIX& mat) { m_mMatrix = mat; }
	D3DXMATRIX getMatrix() { return m_mMatrix; }

private:

	D3DXMATRIX	m_mMatrix;		//�任����
	float		m_fMoveSpeed;	//�ƶ��ٶ�

	LPDIRECT3DDEVICE9		m_pDevice;//d3d�豸
	IDirect3DVertexBuffer9* m_pd3dvb; //���㻺����
	IDirect3DIndexBuffer9*  m_pd3dib; //����������
	LPDIRECT3DTEXTURE9		m_pTexture;//����
};

