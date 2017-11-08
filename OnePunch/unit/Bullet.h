#pragma once
#include "Node.h"
#include "Sprite.h"

//×Óµ¯
class CBullet : public CNode
{
	CBullet(int type);
public:

	enum BulletType
	{
		normal,
		follow,
	};

	~CBullet();

	static CBullet* create(int type) {
		CBullet* p = new CBullet(type);
		return p;
	}

	void update(float dt);

	void setTarget(const D3DXVECTOR3& vPos) { mTargetPos = vPos; }

private:

	void normalMove(float dt);
	void followMove(float dt);

	CSprite * mSpr;
	D3DXVECTOR3 mTargetPos;

	float mAngleSpeed;
	float mMoveSpeed;

	int mType;
};

