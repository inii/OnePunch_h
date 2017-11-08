#include "MyEdit.h"
#include "MainWnd.h"

CMyEdit::CMyEdit()
{
	//多个参数的回调函数
	static int count = 0;
	char str[10];
	sprintf(str, "edit_%d", count++);
	mEditName = str;
	CMainWnd::insertFunc(mEditName,std::bind(&CMyEdit::ProMsg, this, std::placeholders::_1, std::placeholders::_2));

	mBackGround = CSprite::create("ui\\normal.png");
	mBackGround->setPosition(0,0,0);
	addChild(mBackGround, "backg");

	mText = CText::create(mString.c_str());
	mText->setPosition(0, 0, -0.001f);
	addChild(mText, "text");

	mLength = 10;
	bFocus = true;
}

CMyEdit::~CMyEdit()
{
	CMainWnd::removeFunc(mEditName);
}

void CMyEdit::ProMsg(UINT msg, WPARAM wp)
{
	if (!bFocus)return;

	switch (msg)
	{
	case WM_CHAR:
		if ( (wp >= '0' && wp <= '9') || (wp >= 'A' && wp <= 'Z') || (wp >= 'a' && wp <= 'z'))
		{
			if (mString.length() > mLength)
				return;
			mString += wp;
			mText->setString(mString.c_str());
		}
		break;
	case WM_KEYDOWN:
		switch (wp) {
		case VK_BACK: //删除键
			if (mString.size() > 0) {
				mString.pop_back();
				mText->setString(mString.c_str());
			}
			break;
		case VK_RETURN: //回车键
			if (bFocus) bFocus = false;
			break;
		}
		break;
	}
}

void CMyEdit::update(float dt)
{
	CNode::update(dt);

	//POINT pt = CMainWnd::getInstance().getCursorPos();
}