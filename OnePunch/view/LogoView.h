#pragma once
#include "Node.h"

class CLogoView : public CNode
{
	CLogoView();
public:
	~CLogoView();

	static CLogoView* create() {
		CLogoView* p = new CLogoView();
		return p;
	}

	void init();
	void update(float);

private:
	float mCoolDownTime; //µ¹¼ÆÊ±
};

