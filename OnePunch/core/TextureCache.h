#pragma once
#include <d3d9.h>
#include <map>
#include <string>
#include "Texture.h"

//���������
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

	//��������
	CTexture* createTexture(const string& path);
	//��������
	CTexture* findTexture(const string& path);
	//��������
	void insertTexture(const string& path, CTexture* pTex);

	void release();

private:
	map<string, CTexture*> mTextures;
};

