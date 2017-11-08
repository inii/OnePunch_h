#pragma once
#include <d3dx9.h>
#include <string>
#include "Node.h"
using namespace std;

//文本
class CText : public CNode
{
	CText(const string& s);
public:
	~CText();

	static CText* create(const string& s) {
		CText* p = new CText(s);
		return p;
	}

	//设置内容
	void setString(const string& s) { mString = s; }

	virtual void update(float dt);
	virtual void render();

private:

	string mString; //显示文本
	ID3DXFont* mFont;//d3d字体对象

	int mHeight;//字体的高度
	int mWidth;//字体的宽度
};
