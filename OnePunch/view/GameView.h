#pragma once
#include "Node.h"
#include "Sprite.h"
#include "AirPlane.h"

class CGameView : public CNode
{
	CGameView();
public:
	~CGameView();

	static CGameView* create()
	{
		CGameView* p = new CGameView();
		p->init();
		return p;
	}

	void update(float dt);

private:

	void init();
	void updateBg();

	CSprite* mBg1;
	CSprite* mBg2;

	CAirPlane* mMajor;
};

