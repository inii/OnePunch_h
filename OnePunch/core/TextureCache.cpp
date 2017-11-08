#include "TextureCache.h"

CTextureCache::CTextureCache()
{
}

CTextureCache::~CTextureCache()
{
}

void CTextureCache::release()
{
	for (auto it = mTextures.begin(); it != mTextures.end();it++)
	{
		delete it->second;
	}
	mTextures.clear();
}

//��������
CTexture* CTextureCache::createTexture(const string& path)
{
	CTexture* p = findTexture(path);
	if (p)
		return p;

	p = CTexture::create(path, false);
	if (p) {
		mTextures[path] = p;
		return p;
	}

	return NULL;
}

//��������
CTexture* CTextureCache::findTexture(const string& path)
{
	auto it = mTextures.find(path);
	if (it != mTextures.end()) return it->second;
	return NULL;
}

//��������
void CTextureCache::insertTexture(const string& path, CTexture* pTex)
{
	CTexture* p = findTexture(path);
	if (!p)
		mTextures[path] = pTex;
	else {
		string s = "insert texture failed!! path = ";
		s += path;
		s += "\n";
		OutputDebugString(s.c_str());//��ʾ����ʧ��
	}
}