#include "GameView.h"
#include "TextureCache.h"
#include "CmdLine.h"

CGameView::CGameView()
{
}

CGameView::~CGameView()
{
}

void CGameView::updateBg() {

}

void CGameView::init()
{
	//³¡¾°
	mBg1 = CSprite::create("background\\img_bg_level_2.jpg");
	mBg2 = CSprite::create("background\\img_bg_level_2.jpg");

	addChild(mBg1, "bg1");
	addChild(mBg2, "bg2");

	mBg1->setAnchorPos(0.5f, 0, 0);
	mBg2->setAnchorPos(0.5f, 0, 0);

	int screenH = CCmdLine::getInstance().getScreenH();
	int h = mBg2->getTexture()->getHeight();

	mBg1->setPosition(0, -screenH/2, 0);
	mBg2->setPosition(0, -screenH/2-h,0);

	mMajor = CAirPlane::create();
	mMajor->setPosition(0,0,-0.001f);
	addChild(mMajor, "major");
}

void CGameView::update(float dt)
{
	D3DXVECTOR3 v1 = mBg1->getPosition();
	D3DXVECTOR3 v2 = mBg2->getPosition();

	int speed = 60.0f*dt;

	v1.y += speed;
	v2.y += speed;

	int screenH = CCmdLine::getInstance().getScreenH();
	int h = mBg1->getTexture()->getHeight();

	if (v1.y > screenH/2)
		v1.y -= 2*h;
	if (v2.y > screenH/2)
		v2.y -= 2*h;

	mBg1->setPosition(v1);
	mBg2->setPosition(v2);

	CNode::update(dt);
}