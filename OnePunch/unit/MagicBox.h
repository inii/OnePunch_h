#pragma once
#include "node.h"
#include "box.h"
#include <list>
#include <queue>
#include <stack>

enum eTurnType
{
	TURN_NONE,
	TURN_UP,	//��������ǰ��
	TURN_DOWN,
	TURN_LEFT,
	TURN_RIGHT,
	TURN_FRONT,
	TURN_BACK,
};

//ħ����   ����27��box��ϳ�ħ��
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

	//���0.001
	bool isEqual(float f,int i) {
		if (i < f + 0.001f && i > f - 0.003f)
			return true;
		return false;
	}

	//��ʼ��27��box
	void init();

	void update(float dt);

	void render();

	void release();

private:
	//��ת���б�
	void turn(const list<CBox*>& list, eTurnType t);

	void UpdateAllList();

	eTurnType mAction; //����
	float	  mAngle;  //ʣ��ֵ
	float     mSpeed;  //ת���ٶ�

	bool      mAuto; //�Զ���ԭ

	queue<eTurnType> mDeq;
	stack<eTurnType> mStack;//����ջ

	list<CBox*> mBoxs; //����box

	list<CBox*> mRight;
	list<CBox*> mUp;
	list<CBox*> mLeft;
	list<CBox*> mDown;
	list<CBox*> mFront;
	list<CBox*> mBack;
};
