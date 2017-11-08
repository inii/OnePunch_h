#pragma once
#include <d3dx9.h>
#include <string>
#include "Node.h"
using namespace std;

//�ı�
class CText : public CNode
{
	CText(const string& s);
public:
	~CText();

	static CText* create(const string& s) {
		CText* p = new CText(s);
		return p;
	}

	//��������
	void setString(const string& s) { mString = s; }

	virtual void update(float dt);
	virtual void render();

private:

	string mString; //��ʾ�ı�
	ID3DXFont* mFont;//d3d�������

	int mHeight;//����ĸ߶�
	int mWidth;//����Ŀ��
};
