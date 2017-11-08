#pragma once
#include <windows.h>
#include <string>
#include <functional>
#include "Node.h"
#include "TextureCache.h"
#include "Collide.h"
#include "Text.h"

class CMyButton : public CNode
{
	enum ButtonState
	{
		state_normal,
		state_suspend,
		state_clickin,
		state_disable,
	}mState;

	CMyButton();

	CTexture* mNormal;
	CTexture* mSuspend;
	CTexture* mClickin;
	CTexture* mDisable;

	std::function<void()> mClickCallback;

	CCollide mCollide;
	bool mEnable;

	CText* mTitleText;//文本
public:
	~CMyButton();

	void init(
		const string& title,
		const string& normal,
		const string& suspend,
		const string& clickin,
		const string& disable,
		const std::function<void()>& func);

	static CMyButton* create(
		const string& title,
		const string& normal,
		const string& suspend,
		const string& clickin,
		const string& disable,
		const std::function<void()>& func) {
		CMyButton * p = new CMyButton();
		p->init(title, normal, suspend, clickin, disable, func);
		return p;
	}

	void update(float);
	void render();

	//更新碰撞区
	void updateCollide();

	void setEnable(bool b) { mEnable = b; }
	bool getEnable() { return mEnable; }
};

