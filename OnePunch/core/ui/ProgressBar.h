#pragma once
#include "Node.h"
#include "Sprite.h"

//������
class CProgressBar : public CNode
{
	CProgressBar(CSprite* bg, CSprite* front, int style);
	
public:
	enum eStyle
	{
		style_horizontal,	//ˮƽ��
		style_Vertical,		//��ֱ��
		style_cycle,		//Բ��
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
	float	 mPercent;		//�ٷֱ�  0-1
	CSprite* mBackground;	//��ͼ
	CSprite* mFront;		//��ʾ���ȵ�ͼ
};

