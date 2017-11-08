#pragma once
#include <d3d9.h>
#include <string>
#include "Node.h"
#include "TextureCache.h"
#include "Collide.h"

//精灵类
using namespace std;
class CSprite : public CNode
{
	CSprite(const string& path);
public:
	CSprite();
	~CSprite();

	static CSprite* create(const string& path) {
		CSprite* p = new CSprite(path);
		return p;
	}

	virtual void update(float dt);
	virtual void render();

	CTexture* getTexture() { return mTexture; }

	void setRect(CRect r) { mRect = r; };
	CRect getRect() { return mRect; }

private:
	CRect mRect;
protected:
	CTexture* mTexture;//纹理指针
};

