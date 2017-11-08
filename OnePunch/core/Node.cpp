#include "Node.h"

CNode::CNode()
:mParent(nullptr)
,name("default")
,isVisible(true)
,isPreRemove(false)
{
	D3DXMatrixIdentity(&m_mMatrix);
	m_vPos.x = m_vPos.y = m_vPos.z = 0;
	m_vScale.x = m_vScale.y = m_vScale.z = 1;
	m_vRotate.x = m_vRotate.y = m_vRotate.z = 0;
	m_vAnchorPos.x = m_vAnchorPos.y = m_vAnchorPos.z = 0.5f;
	m_color = D3DCOLOR_ARGB(255,255,255,255);
}

CNode::~CNode()
{
}

//把其他节点从父节点删除
void CNode::removeFromParent()
{
	//将其从父节点的容器中清除
	CNode* pParent = getParent();
	if (pParent) {
		auto it = pParent->mChildren.find(name);
		if(it != pParent->mChildren.end())
			pParent->mChildren.erase(it);
	}

	//删除所有的子节点
	for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
		CNode* p = it->second;
		p->mParent = NULL; //先去掉父节点
		p->removeFromParent();
	}
	mChildren.clear();

	delete this;
}

//删除子节点
bool CNode::removeChildByName(const string& name)
{
	auto it = mChildren.find(name);
	
	if (it != mChildren.end()) {
		CNode* p = it->second;
		//删除自己
		p->removeFromParent();
		mChildren.erase(it);
	}

	return true;
}

//删除自己
void CNode::removeSelf()
{
	isPreRemove = true;
}

bool CNode::addChild(CNode* pChild, const string& name)
{
	if (!pChild) return false;

	auto it = mChildren.find(name);
	if (it != mChildren.end()) {
		OutputDebugString("error! addChild() this name is exist!");
		return false;
	}

	pChild->setName(name);
	pChild->mParent = this;
	mChildren[name] = pChild;
	return true;
}

void CNode::update(float dt)
{
	//先计算自己的矩阵
	CNode* pParent = getParent();
	D3DXMATRIX mMat;
	if (pParent)
		mMat = pParent->getMatrix();
	else
		D3DXMatrixIdentity(&mMat);

	//平移
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, m_vPos.x, m_vPos.y, m_vPos.z);
	//缩放
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, m_vScale.x, m_vScale.y, m_vScale.z);
	//旋转
	D3DXMATRIX rotateX;
	D3DXMatrixRotationX(&rotateX, m_vRotate.x);
	D3DXMATRIX rotateY;
	D3DXMatrixRotationY(&rotateY, m_vRotate.y);
	D3DXMATRIX rotateZ;
	D3DXMatrixRotationZ(&rotateZ, m_vRotate.z);
	m_mMatrix = scale*rotateY*rotateX*rotateZ*trans;

	m_mMatrix = m_mMatrix * mMat;

	//清除移除标志为真的节点
	for (auto it = mChildren.begin(); it != mChildren.end();) {
		CNode* pNode = it->second;
		if (pNode->isPreRemove) {
			it = mChildren.erase(it);
			pNode->removeFromParent();
		}
		else
			it++;
	}

	//然后调用子节点
	for (auto it = mChildren.begin(); it != mChildren.end(); it++){
		it->second->update(dt);
	}
}

void CNode::render()
{
	for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
		if(it->second)
			it->second->render();
	}
}

CNode* CNode::getChildByName(const string& name)
{
	auto it = mChildren.find(name);
	if (it != mChildren.end()) {
		return it->second;
	}

	return nullptr;
}