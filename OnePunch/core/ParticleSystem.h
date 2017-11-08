#pragma once
#include <list>
#include <d3d9.h>
#include <d3dx9math.h>
#include "node.h"

using namespace std;
//����ϵͳ
class CParticleSystem : public CNode
{
	D3DXVECTOR3 vPos0;  //��ʼλ��  -->�����  -->������
	D3DXVECTOR3 vSpeed0;//��ʼ�ٶ�
	D3DXVECTOR3 vGravityAddSpeed;//�������ٶ�
	float mLiveTime; //��������

	struct Particle
	{
		D3DXVECTOR3 vPos;		//λ��
		D3DXVECTOR3 vSpeed;		//�ٶ�

		float		fKeepTime;	//����ʱ��
		D3DCOLOR	curRGB;		//��ǰ��ɫ
	};

	struct vertexData
	{
		float x, y, z;
		DWORD color;
	};
	DWORD VERTEX_FVF;//�����ʽ


	struct vetrexNode {
		float x, y, z;
		float nx, ny, nz;
	};

public:
	CParticleSystem();
	~CParticleSystem();

	//����һ������
	void add();
	//�ͷ�
	void release();
	//��ʼ��
	void init();
	//����
	void update(float dt);
	//��Ⱦ
	void render();

private:

	//�����ʼλ��
	D3DXVECTOR3 culcPos0();

	int nMaxNum; //���������

	ID3DXMesh* mpMesh;

	list<Particle*> mDeads; //��������
	list<Particle*> mLives; //�����

	int mBufferSize;	//��������С

	LPDIRECT3DDEVICE9		m_pDevice;//d3d�豸
	LPDIRECT3DTEXTURE9		m_pTexture;//����1
	IDirect3DVertexBuffer9* m_pVB;    //���㻺����
};

