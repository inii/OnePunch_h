#include "Texture.h"
#include "D3DDevice.h"
#include "MainWnd.h"

CTexture::~CTexture()
{
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CTexture* CTexture::create(const string& path, bool bMipmap)
{
	CTexture* pTexture = new CTexture();
	if (!pTexture->initWithPath(path, bMipmap)) {
		delete pTexture;
		return NULL;
	}

	return pTexture;
}

bool CTexture::initWithPath(const string& path, bool bMipmap)
{
	LPDIRECT3DDEVICE9 pDevice = CD3DDevice::getInstance().getDevice();
	if (FAILED(D3DXCreateTextureFromFileEx(pDevice, path.c_str(),
		D3DX_DEFAULT, D3DX_DEFAULT,
		bMipmap ? 0 : 1,	// Mip levels
		0,					// Usage
		D3DFMT_A8R8G8B8,	// Format
		D3DPOOL_MANAGED,	// Memory pool
		D3DX_FILTER_NONE,	// Filter
		D3DX_DEFAULT,		// Mip filter
		0,					// Color key
		&mInfo, NULL,
		&m_pTexture)))
	{
		HWND hwnd = CMainWnd::getInstance().getMainWnd();
		MessageBox(hwnd, "º”‘ÿŒ∆¿Ì ß∞‹", "æØ∏Ê", MB_OK);

		return false;
	}

	return true;
}