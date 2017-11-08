#pragma once
#include "Node.h"
#include "Sprite.h"

//·É»ú
class CAirPlane : public CNode
{
	CAirPlane();
public:
	~CAirPlane();

	static CAirPlane* create() {
		CAirPlane* p = new CAirPlane();
		return p;
	}

	void update(float dt);

private:

	CSprite* mSpr;
	float m_fMoveSpeed;

	float m_fFireCoolDownTime;
	float m_fFireCountTime;
};

