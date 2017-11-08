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

//创建纹理
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

//查找纹理
CTexture* CTextureCache::findTexture(const string& path)
{
	auto it = mTextures.find(path);
	if (it != mTextures.end()) return it->second;
	return NULL;
}

//插入纹理
void CTextureCache::insertTexture(const string& path, CTexture* pTex)
{
	CTexture* p = findTexture(path);
	if (!p)
		mTextures[path] = pTex;
	else {
		string s = "insert texture failed!! path = ";
		s += path;
		s += "\n";
		OutputDebugString(s.c_str());//提示插入失败
	}
}