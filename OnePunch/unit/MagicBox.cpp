#include "MagicBox.h"
#include "d3ddevice.h"
#include "input.h"

CMagicBox::CMagicBox()
{
	mAction = TURN_NONE;
	mAngle = 0.0f;
	mSpeed = 6.0f;
	mAuto = false;
}

CMagicBox::~CMagicBox()
{
}

void CMagicBox::init()
{
	for (int i = 0; i < 3;i++) {
		for (int j = 0; j < 3;j++) {
			for (int k = 0; k < 3;k++) {
				CBox* p = CBox::create();

				D3DXMATRIX mat = p->getMatrix();
				mat._41 = (i - 1) * 2;
				mat._42 = (j - 1) * 2;
				mat._43 = (k - 1) * 2;
				p->setMatrix(mat);

				p->pos.x = i-1;
				p->pos.y = j-1;
				p->pos.z = k-1;

				mBoxs.push_back(p);
			}
		}
	}

	UpdateAllList();
}

void CMagicBox::UpdateAllList()
{
	mLeft.clear();
	mRight.clear();
	mUp.clear();
	mFront.clear();
	mBack.clear();
	mDown.clear();
	for (list<CBox*>::iterator it = mBoxs.begin(); it != mBoxs.end(); it++) {
		CBox* p = *it;
		if (isEqual(p->pos.x, -1)) { mLeft.push_back(p); }
		if (isEqual(p->pos.x, 1)) { mRight.push_back(p); }
		if (isEqual(p->pos.y, -1)) { mDown.push_back(p); }
		if (isEqual(p->pos.y, 1)) { mUp.push_back(p); }
		if (isEqual(p->pos.z, -1)) { mFront.push_back(p); }
		if (isEqual(p->pos.z, 1)) { mBack.push_back(p); }
	}
}

//旋转该列表
void CMagicBox::turn(const list<CBox*>& list, eTurnType t)
{
	if (mAngle <= 0) {
		D3DXMATRIX mat;
		float f = D3DX_PI/2;
		if (mAuto) f = -f;

		switch (t)
		{
		case TURN_UP:
			D3DXMatrixRotationY(&mat, f);
			break;
		case TURN_DOWN:
			D3DXMatrixRotationY(&mat, -f);
			break;
		case TURN_LEFT:
			D3DXMatrixRotationX(&mat, f);
			break;
		case TURN_RIGHT:
			D3DXMatrixRotationX(&mat, -f);
			break;
		case TURN_FRONT:
			D3DXMatrixRotationZ(&mat, f);
			break;
		case TURN_BACK:
			D3DXMatrixRotationZ(&mat, -f);
			break;
		default:
			break;
		}

		//向量跟矩阵做转换
		for (auto it = list.begin(); it != list.end(); it++) {
			D3DXVec3TransformCoord(&(*it)->pos, &(*it)->pos, &mat);
		}

		UpdateAllList();

		mAction = TURN_NONE;
		return;
	}

	float f = D3DX_PI / 180* mSpeed;
	if (mAngle < f) {
		f = mAngle;
	}
	mAngle -= f;

	if (mAuto) f = -f;

	D3DXMATRIX mat;
	switch (t)
	{
	case TURN_UP:
		D3DXMatrixRotationY(&mat, f);
		break;
	case TURN_DOWN:
		D3DXMatrixRotationY(&mat, -f);
		break;
	case TURN_LEFT:
		D3DXMatrixRotationX(&mat, f);
		break;
	case TURN_RIGHT:
		D3DXMatrixRotationX(&mat, -f);
		break;
	case TURN_FRONT:
		D3DXMatrixRotationZ(&mat, f);
		break;
	case TURN_BACK:
		D3DXMatrixRotationZ(&mat, -f);
		break;
	default:
		break;
	}

	for (auto it = list.begin(); it != list.end(); it++) {
		auto m = (*it)->getMatrix();
		m *= mat;
		(*it)->setMatrix(m);
	}
}

void CMagicBox::update(float dt)
{
	CNode::update(dt);

	if (mAction == TURN_NONE)
	{
		if (!mDeq.empty()) {
			mAction = mDeq.front();
			mAngle = D3DX_PI / 2;//设置需要旋转的角度为90度

			if(!mAuto)
				mStack.push(mAction);

			mDeq.pop();
		}
		else {
			mAuto = false;
		}
	}

	switch (mAction)
	{
	case TURN_UP:
		turn(mUp, mAction);
		break;
	case TURN_DOWN:
		turn(mDown, mAction);
		break;
	case TURN_LEFT:
		turn(mLeft, mAction);
		break;
	case TURN_RIGHT:
		turn(mRight, mAction);
		break;
	case TURN_FRONT:
		turn(mFront, mAction);
		break;
	case TURN_BACK:
		turn(mBack, mAction);
		break;
	default:
		break;
	}

	if (mAuto) return;

	CInput& input = CInput::getInstance();
	if (input.keyUp(DIK_Q)) mDeq.push(TURN_LEFT);
	if (input.keyUp(DIK_W)) mDeq.push(TURN_RIGHT);
	if (input.keyUp(DIK_E)) mDeq.push(TURN_UP);
	if (input.keyUp(DIK_R)) mDeq.push(TURN_DOWN);
	if (input.keyUp(DIK_T)) mDeq.push(TURN_FRONT);
	if (input.keyUp(DIK_Y)) mDeq.push(TURN_BACK);

	if (mAction == TURN_NONE && input.keyUp(DIK_SPACE)) //自动还原
	{
		mAuto = true;
		while (!mStack.empty()) {
			mDeq.push(mStack.top());
			mStack.pop();
		}
	}
}

void CMagicBox::render()
{
	CNode::render();
	D3DXMATRIX mat = getMatrix();

	for (list<CBox*>::iterator it = mBoxs.begin(); it != mBoxs.end(); it++) {

		CBox* pBox = *it;
		D3DXMATRIX boxMat = pBox->getMatrix();

		boxMat = boxMat * mat;

		LPDIRECT3DDEVICE9 pDevice = CD3DDevice::getInstance().getDevice();
		pDevice->SetTransform(D3DTS_WORLD, &boxMat);

		pBox->render();
	}
}

void CMagicBox::release()
{
	for (list<CBox*>::iterator it = mBoxs.begin(); it != mBoxs.end(); it++) {
		(*it)->release();
		delete *it;
	}
	mBoxs.clear();
}