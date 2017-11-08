#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <map>

//������
using namespace std;
class CTexture
{
	CTexture() {}
public:
	~CTexture();

	static CTexture* create(const string& path, bool bMipmap=false);

	UINT getWidth() { return mInfo.Width; }
	UINT getHeight() { return mInfo.Height; }
	D3DFORMAT getFormat() { return mInfo.Format; }
	//��ȡ����
	LPDIRECT3DTEXTURE9 getD3dTex() {return m_pTexture;}

private:

	bool initWithPath(const string& path, bool bMipmap);

	//����
	LPDIRECT3DTEXTURE9		m_pTexture;
	//ͼƬ��Ϣ
	D3DXIMAGE_INFO			mInfo;
};

