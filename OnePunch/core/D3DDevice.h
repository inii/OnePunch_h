#pragma once
#include <d3d9.h>
#include <d3dx9.h>

//d3d���� �豸���������
class CD3DDevice
{
	CD3DDevice();

	//d3d����
	LPDIRECT3D9			m_pD3d;
	//d3d�豸����
	LPDIRECT3DDEVICE9	m_pDevice;
	//�������
	ID3DXSprite*		m_pSprite;

public:
	~CD3DDevice();

	static CD3DDevice& getInstance()
	{
		static CD3DDevice s;
		return s;
	}

	HRESULT init();

	LPDIRECT3DDEVICE9 getDevice() { return m_pDevice; }
	ID3DXSprite* getSprite() { return m_pSprite; }

};

