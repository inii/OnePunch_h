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

	//�����༭��
	static CMyEdit* create() {//����...
		CMyEdit * p = new CMyEdit();
		return p;
	}

	void update(float dt);

private:

	void ProMsg(UINT msg, WPARAM wp);

	bool     bFocus;//�Ƿ��н���

	CText*   mText;
	CSprite* mBackGround; //����ͼ
	string   mString;
	int      mLength; //��󳤶�

	string   mEditName;
};

