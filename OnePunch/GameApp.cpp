#include "GameApp.h"
#include "d3ddevice.h"
#include "camera.h"
#include "Input.h"
#include "Sprite.h"
#include "MainWnd.h"
#include "LogoView.h"
#include "CmdLine.h"
#include "Text.h"
#include <string>

#include ".\\plugin\\tinyxml\\tinyxml.h"

CGameApp::CGameApp()
{
	mRoot = new CNode;
}

CGameApp::~CGameApp()
{
}

void CGameApp::add2dScene(CNode* pChild, const string& name)
{
	int w = CCmdLine::getInstance().getScreenW();
	int h = CCmdLine::getInstance().getScreenH();

	pChild->setPosition(w / 2, h / 2, 0.01f);
	getRoot2d()->addChild(pChild, name);
}

bool CGameApp::init()
{
	if (FAILED(CD3DDevice::getInstance().init()))
		return false;
	CInput::getInstance().init();

	m_pDevice = CD3DDevice::getInstance().getDevice();
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//逆时针裁剪

	m_pDevice->SetRenderState(D3DRS_ZENABLE, true);
	m_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	m_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	CNode* node = NULL;
	node = new CNode();
	node->setAnchorPos(D3DXVECTOR3(0.5f, 0.5f, 0));
	mRoot->addChild(node, "Root2d");

	int w = CCmdLine::getInstance().getScreenW();
	int h = CCmdLine::getInstance().getScreenH(); 

	//显示FPS
	CText* titleText = CText::create("111");
	titleText->setPosition(D3DXVECTOR3(0, h, 0));
	titleText->setAnchorPos(D3DXVECTOR3(0, 1, 0));
	titleText->setScale(D3DXVECTOR3(0.5, 0.5, 0.5));
	titleText->setColor(D3DCOLOR_XRGB(255,0,0));
	getRoot2d()->addChild(titleText, "FPS");

	CLogoView* pview = CLogoView::create();
	add2dScene(pview, "logoview");

	return true;
}

void CGameApp::update(float dt)
{
	CInput::getInstance().update();
	getRoot2d()->update(dt);

	if (CInput::getInstance().keyDown(DIK_F1)) {
		m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);
	}
	if (CInput::getInstance().keyDown(DIK_F2)) {
		m_pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	}

	CText* p = (CText*)getRoot2d()->getChildByName("FPS");
	float fps = 1.0f / dt;
	char str[32];
	sprintf(str, "FPS:%.5f", fps);
	p->setString(str);
}

void CGameApp::render()
{
	//后台颜色缓冲区 清空
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

	m_pDevice->BeginScene();
	auto pSprite = CD3DDevice::getInstance().getSprite();
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	getRoot2d()->render();
	pSprite->End();
	m_pDevice->EndScene();

	m_pDevice->Present(NULL, NULL, NULL, NULL);//翻转 后台缓冲区数据拷贝到前台颜色缓冲区 显示出来
}

void CGameApp::release()
{
	mRoot->removeFromParent();
}
