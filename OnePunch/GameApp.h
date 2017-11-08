#pragma once
#include <d3d9.h>
#include "node.h"

class CGameApp
{
	CGameApp();
public:
	~CGameApp();

	static CGameApp& getInstance()
	{
		static CGameApp s;
		return s;
	}

	bool init();
	void update(float dt); //�߼�����
	void render(); //��Ⱦ
	void release();

	CNode* getRoot2d() { return mRoot->getChildByName("Root2d"); }
	CNode* getRoot3d() { return mRoot->getChildByName("Root3d"); }

	void add2dScene(CNode* pChild, const string& name); //��root2d�Ľڵ������ӵ��ӽڵ�
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	CNode*	 mRoot;
};

