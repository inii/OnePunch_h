#pragma once
#include "Node.h"
#include "Sprite.h"

//进度条
class CProgressBar : public CNode
{
	CProgressBar(CSprite* bg, CSprite* front, int style);
	
public:
	enum eStyle
	{
		style_horizontal,	//水平的
		style_Vertical,		//垂直的
		style_cycle,		//圆的
	};

	~CProgressBar();

	static CProgressBar* create(CSprite* bg, CSprite* front, int style=style_horizontal) {
		CProgressBar * p = new CProgressBar(bg, front, style);
		return p;
	}

	void setPercent(float f) {
		mPercent = f; 
		if (mPercent > 1.0f)
			mPercent = 1.0f;
		if (mPercent <= 0.0f)
			mPercent = 0.0f;
	}

	void update(float dt);

private:
	eStyle   mStyle;
	float	 mPercent;		//百分比  0-1
	CSprite* mBackground;	//底图
	CSprite* mFront;		//表示进度的图
};

