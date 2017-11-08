#include "ProgressBar.h"

CProgressBar::CProgressBar(CSprite* bg, CSprite* front, int style)
{
	mStyle = (eStyle)style;

	mBackground = bg;
	addChild(bg, "background");
	bg->setPosition(D3DXVECTOR3(0,0,0.01f));

	mFront = front;
	addChild(front, "front");
	front->setPosition(D3DXVECTOR3(0, 0, 0.001f));

	mPercent = 0.0f;
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::update(float dt)
{
	CNode::update(dt);

	switch (mStyle)
	{
	case CProgressBar::style_horizontal:
	{

		CRect r = mFront->getRect();
		r.right = mPercent;
		if (r.right > 1.0f) r.right = 1.0f;

		mFront->setRect(r);
	}
		break;
	case CProgressBar::style_Vertical:
	{
		CRect r = mFront->getRect();
		r.top = 1-mPercent;
		if (r.top < 0.0f) r.top = 0.0f;
		mFront->setRect(r);

		D3DXVECTOR3 v = mFront->getPosition();
		int h = mFront->getTexture()->getHeight();
		v.y = h*(1-mPercent);
		mFront->setPosition(v);
	}
		break;
	case CProgressBar::style_cycle:
		break;
	default:
		break;
	}
}
