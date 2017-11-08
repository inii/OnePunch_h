#pragma once
#include "Node.h"
#include "MyButton.h"

//�˵�����
class CMenuView : public CNode
{
	CMenuView();
public:
	~CMenuView();


	static CMenuView* create() {
		CMenuView* p = new CMenuView();
		p->init();
		return p;
	}

	void init();
	void update(float);

	void onClickBeginGame();
	void onClickQuitGame();
	void onClickxxxx();

private:
	CMyButton* bnt1;
	CMyButton* bnt2;
	CMyButton* bnt3;
};

