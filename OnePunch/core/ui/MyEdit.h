#pragma once
#include "Sprite.h"
#include "Text.h"
#include <string>

using namespace std;

class CMyEdit : public CNode
{
	CMyEdit();
public:
	~CMyEdit();

	//创建编辑框
	static CMyEdit* create() {//参数...
		CMyEdit * p = new CMyEdit();
		return p;
	}

	void update(float dt);

private:

	void ProMsg(UINT msg, WPARAM wp);

	bool     bFocus;//是否有焦点

	CText*   mText;
	CSprite* mBackGround; //背景图
	string   mString;
	int      mLength; //最大长度

	string   mEditName;
};

