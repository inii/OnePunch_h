#include "LogoView.h"
#include "Sprite.h"
#include "GameApp.h"
#include "MenuView.h"
#include "ProgressBar.h"
#include "Text.h"
#include "CmdLine.h"
#include <fstream>

CLogoView::CLogoView()
{
	mCoolDownTime = 2.0f;
	init();
}

CLogoView::~CLogoView()
{
}

void CLogoView::init()
{
	CSprite* spr = CSprite::create("background\\tencentlogo.png");
	spr->setScale(0.8f,0.8f,0.8f);
	addChild(spr, "logo");

	//CSprite* p1 = CSprite::create("ui\\progress1.png");
	//CSprite* p2 = CSprite::create("ui\\progress2.png");

	//CProgressBar* pro = CProgressBar::create(p1, p2);
	//pro->setPosition(0, 0, 0.01f);
	////pro->setRotate(0, 0, -D3DX_PI / 2);
	//addChild(pro, "progress");

	//CText* text = CText::create("120/999");
	//pro->setPosition(0, 0, 0.001f);
	//addChild(text, "hp");
}

void CLogoView::update(float dt)
{
	CNode::update(dt);

	static float time = 0;
	time += dt;

	//CProgressBar* p = (CProgressBar*)getChildByName("progress");
	//p->setPercent(time/5.0f);

	if (time > mCoolDownTime)
	{
		OutputDebugString("时间到了！！切换界面");
		CMenuView* pView = CMenuView::create();
		CGameApp::getInstance().add2dScene(pView, "menuview");

		removeSelf();
	}
}
