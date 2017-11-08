#include "MenuView.h"
#include "Sprite.h"
#include "FrameSprite.h"
#include "ProgressBar.h"
#include "GameView.h"
#include "GameApp.h"
#include "MyEdit.h"

CMenuView::CMenuView()
{
	m_vAnchorPos.z = 0.0f;
}

CMenuView::~CMenuView()
{
}

void CMenuView::onClickBeginGame()
{
	CGameView* p = CGameView::create();
	CGameApp::getInstance().add2dScene(p, "game");

	removeSelf();
}

void CMenuView::onClickQuitGame()
{

}

void CMenuView::onClickxxxx()
{

}

void CMenuView::init()
{
	CSprite* spr = CSprite::create("background\\img_bg_logo.jpg");
	spr->setPosition(0,0,0.005f);
	addChild(spr, "background");

	bnt1 = CMyButton::create("1111",
		"ui\\btn_1.png",
		"ui\\btn_2.png",
		"ui\\btn_8.png",
		"ui\\btn_0.png",
		std::bind(&CMenuView::onClickBeginGame, this));
	bnt1->setPosition(0,0,-0.001f);
	bnt1->setScale(0.4f, 0.4f, 0.4f);
	addChild(bnt1, "button1");

	bnt2 = CMyButton::create("2222",
		"ui\\btn_1.png",
		"ui\\btn_2.png",
		"ui\\btn_8.png",
		"ui\\btn_0.png",
		std::bind(&CMenuView::onClickxxxx, this));
	bnt2->setPosition(0, 100, -0.001f);
	bnt2->setScale(0.4f, 0.4f, 0.4f);
	addChild(bnt2, "button2");

	bnt3 = CMyButton::create("3333",
		"ui\\btn_1.png",
		"ui\\btn_2.png",
		"ui\\btn_8.png",
		"ui\\btn_0.png",
		std::bind(&CMenuView::onClickQuitGame, this));
	bnt3->setPosition(0, 200, -0.001f);
	bnt3->setScale(0.4f, 0.4f, 0.4f);
	addChild(bnt3, "button3");

	CMyEdit* myEdit = CMyEdit::create();
	myEdit->setPosition(0,-100, -0.001f);
	addChild(myEdit, "edit");

	//CFrameSprite* pFrame = CFrameSprite::create("framesprite\\bomb2\\image_ (%d).png", 10, true);
	//pFrame->setPosition(0,-100, -0.001f);
	//addChild(pFrame, "bomb");
}

void CMenuView::update(float dt)
{
	CNode::update(dt);
}