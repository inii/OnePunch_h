#pragma once
#include "node.h"
#include "box.h"
#include <list>
#include <queue>
#include <stack>

enum eTurnType
{
	TURN_NONE,
	TURN_UP,	//上下左右前后
	TURN_DOWN,
	TURN_LEFT,
	TURN_RIGHT,
	TURN_FRONT,
	TURN_BACK,
};

//魔方类   管理27个box组合成魔方
class CMagicBox : public CNode
{
	CMagicBox();
public:
	~CMagicBox();

	static CMagicBox* create() {
		CMagicBox* p = new CMagicBox();
		p->init();
		return p;
	}

	//误差0.001
	bool isEqual(float f,int i) {
		if (i < f + 0.001f && i > f - 0.003f)
			return true;
		return false;
	}

	//初始化27个box
	void init();

	void update(float dt);

	void render();

	void release();

private:
	//旋转该列表
	void turn(const list<CBox*>& list, eTurnType t);

	void UpdateAllList();

	eTurnType mAction; //动作
	float	  mAngle;  //剩余值
	float     mSpeed;  //转动速度

	bool      mAuto; //自动还原

	queue<eTurnType> mDeq;
	stack<eTurnType> mStack;//命令栈

	list<CBox*> mBoxs; //所有box

	list<CBox*> mRight;
	list<CBox*> mUp;
	list<CBox*> mLeft;
	list<CBox*> mDown;
	list<CBox*> mFront;
	list<CBox*> mBack;
};
