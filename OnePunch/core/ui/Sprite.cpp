#include "Sprite.h"
#include "GameApp.h"
#include "D3DDevice.h"

CSprite::CSprite(const string& path)
{
	mTexture = CTextureCache::getInstance().createTexture(path);
	m_vAnchorPos.z = 0.0f;

	mRect.left = 0;
	mRect.top = 0;
	mRect.right = 1.0f;
	mRect.bottom = 1.0f;
}

CSprite::CSprite()
{
	mTexture = NULL;
	m_vAnchorPos.z = 0.0f;

	mRect.left = 0;
	mRect.top = 0;
	mRect.right = 1.0f;
	mRect.bottom = 1.0f;
}

CSprite::~CSprite()
{
}

void CSprite::update(float dt)
{
	CNode::update(dt);
}

void CSprite::render()
{
	CNode::render();
	if (!mTexture) return;

	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->SetTransform(&m_mMatrix);

	int w = mTexture->getWidth();
	int h = mTexture->getHeight();

	D3DXVECTOR3 v = m_vAnchorPos;
	v.x = w*v.x;
	v.y = h*v.y;

	RECT r;
	r.left = mRect.left*mTexture->getWidth();
	r.right = mRect.right*mTexture->getWidth();
	r.top = mRect.top*mTexture->getHeight();
	r.bottom = mRect.bottom*mTexture->getHeight();

	pSprite->Draw(mTexture->getD3dTex(), &r, &v, NULL, m_color);
}
