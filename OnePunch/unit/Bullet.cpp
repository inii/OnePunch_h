#include "Bullet.h"
#include "Input.h"

CBullet::CBullet(int type)
{
	mAngleSpeed = 5.0f;
	mMoveSpeed = 720.0f;

	mType = type;
	if(type == normal)
		mSpr = CSprite::create("plane\\myb_1.png");
	else if (type == follow) {
		mSpr = CSprite::create("plane\\image3073.png");
	}
	addChild(mSpr, "bullet_sprite");
}

CBullet::~CBullet()
{
}

void CBullet::normalMove(float dt)
{
	D3DXVECTOR3 v = { 0, -1, 0 };//正方向
	 
	D3DXMATRIX rotateX;//欧拉角旋转
	D3DXMatrixRotationX(&rotateX, m_vRotate.x);
	D3DXMATRIX rotateY;
	D3DXMatrixRotationY(&rotateY, m_vRotate.y);
	D3DXMATRIX rotateZ;
	D3DXMatrixRotationZ(&rotateZ, m_vRotate.z);
	D3DXMATRIX mat = rotateY*rotateX*rotateZ;
	D3DXVec3TransformCoord(&v, &v, &mat);
	D3DXVec3Normalize(&v, &v);

	m_vPos += v*mMoveSpeed*dt;
}

void CBullet::followMove(float dt)
{
	if (m_vRotate.z > D3DX_PI * 2)
		m_vRotate.z -= D3DX_PI * 2;

	if (m_vRotate.z < 0)
		m_vRotate.z += D3DX_PI * 2;

	float targetAngle = atan(-(m_vPos.x-mTargetPos.x) / (m_vPos.y-mTargetPos.y));
	if (m_vPos.y - mTargetPos.y < 0)//如果大于180度
		targetAngle += D3DX_PI;
	if (targetAngle < 0) targetAngle += D3DX_PI * 2; //小于0度 + 360 将角度限制在0-2pi

	float f = fabs(targetAngle - m_vRotate.z);
	if (f < D3DX_PI) {
		if (targetAngle > m_vRotate.z)
			m_vRotate.z += mAngleSpeed*dt;
		else
			m_vRotate.z -= mAngleSpeed*dt;
	}
	else {
		if (targetAngle > m_vRotate.z)
			m_vRotate.z -= mAngleSpeed*dt;
		else
			m_vRotate.z += mAngleSpeed*dt;
	}

	D3DXVECTOR3 v = { 0, -1, 0 };//正方向

	D3DXMATRIX rotateX;//欧拉角旋转
	D3DXMatrixRotationX(&rotateX, m_vRotate.x);
	D3DXMATRIX rotateY;
	D3DXMatrixRotationY(&rotateY, m_vRotate.y);
	D3DXMATRIX rotateZ;
	D3DXMatrixRotationZ(&rotateZ, m_vRotate.z);
	D3DXMATRIX mat = rotateY*rotateX*rotateZ;
	D3DXVec3TransformCoord(&v, &v, &mat);
	D3DXVec3Normalize(&v, &v);

	m_vPos += v*mMoveSpeed*dt;
}

void CBullet::update(float dt)
{
	if (mType == normal) {
		normalMove(dt);
	}
	else if (mType == follow) {
		followMove(dt);
	}

	CNode::update(dt);

	if (m_mMatrix._42 <= -30) {
		this->removeSelf();
		return;
	}
}