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
	void update(float dt); //逻辑更新
	void render(); //渲染
	void release();

	CNode* getRoot2d() { return mRoot->getChildByName("Root2d"); }
	CNode* getRoot3d() { return mRoot->getChildByName("Root3d"); }

	void add2dScene(CNode* pChild, const string& name); //在root2d的节点上增加的子节点
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	CNode*	 mRoot;
};

