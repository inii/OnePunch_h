#include "AirPlane.h"
#include "Input.h"
#include "Bullet.h"

CAirPlane::CAirPlane()
{
	m_fMoveSpeed = 180.0f;
	m_fFireCoolDownTime = 0.3f;
	m_fFireCountTime = m_fFireCoolDownTime;
	mSpr = CSprite::create("plane\\BluePlane.png");
	addChild(mSpr, "plane_sprite");
}

CAirPlane::~CAirPlane()
{
}

void CAirPlane::update(float dt)
{
	m_fFireCountTime -= dt;
	CInput& input = CInput::getInstance();

	if (input.keyHold(DIK_A) || input.keyHold(DIK_LEFT)) {
		m_vPos.x -= m_fMoveSpeed*dt;
	}

	if (input.keyHold(DIK_D) || input.keyHold(DIK_RIGHT)) {
		m_vPos.x += m_fMoveSpeed*dt;
	}

	if (input.keyHold(DIK_W) || input.keyHold(DIK_UP)) {
		m_vPos.y -= m_fMoveSpeed*dt;
	}

	if (input.keyHold(DIK_S) || input.keyHold(DIK_DOWN)) {
		m_vPos.y += m_fMoveSpeed*dt;
	}

	if (input.keyHold(DIK_J) || input.keyHold(DIK_NUMPAD0)){//发子弹
		if (m_fFireCountTime <= 0.0f)
		{
			static int i = 0;
			m_fFireCountTime = m_fFireCoolDownTime;

			for (int j = 0; j<3; j++)
			{
				CBullet* bullet = CBullet::create(CBullet::normal);

				char str[32];
				sprintf(str, "bullet_%d", i++);

				D3DXVECTOR3 v = this->getPosition();
				v.z -= 0.001f;
				v.y -= 50.0f;
				bullet->setPosition(v);

				bullet->setRotate(0, 0, D3DX_PI / 180 * 12 * (j - 1));
				this->getParent()->addChild(bullet, str);
				bullet->update(dt);
			}
		}
	}

	if (input.keyHold(DIK_K) || input.keyHold(DIK_NUMPAD1)) {//发子弹
		if (m_fFireCountTime <= 0.0f)
		{
			static int i = 0;
			m_fFireCountTime = m_fFireCoolDownTime;

			for (int j = 0; j < 5; j++)
			{
				CBullet* bullet = CBullet::create(CBullet::follow);

				static int k = 0;
				char str[32];
				sprintf(str, "follow_bullet_%d", k++);

				D3DXVECTOR3 v = this->getPosition();
				v.z -= 0.001f;
				v.y -= 50.0f;
				bullet->setPosition(v);

				bullet->setTarget(D3DXVECTOR3(0,0,0));
				bullet->setRotate(0, 0, D3DX_PI / 180 * 30 * (j - 2));
				this->getParent()->addChild(bullet, str);
				bullet->update(dt);
			}
		}
	}

	CNode::update(dt);
}