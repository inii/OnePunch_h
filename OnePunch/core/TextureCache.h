#pragma once
#include <d3d9.h>
#include <map>
#include <string>
#include "Texture.h"

//纹理缓存管理
using namespace std;
class CTextureCache
{
	CTextureCache();
public:
	~CTextureCache();

	static CTextureCache& getInstance() {
		static CTextureCache s;
		return s;
	}

	//创建纹理
	CTexture* createTexture(const string& path);
	//查找纹理
	CTexture* findTexture(const string& path);
	//插入纹理
	void insertTexture(const string& path, CTexture* pTex);

	void release();

private:
	map<string, CTexture*> mTextures;
};

