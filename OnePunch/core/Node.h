#pragma once
#include <string>
#include <map>
#include <d3dx9math.h>

using namespace std;
//节点
class CNode
{
	friend class CGameApp;
public:
	CNode();
	virtual ~CNode();

	bool addChild(CNode* pChild, const string& name);

	//从父节点删除
	void removeFromParent();
	//删除子节点
	bool removeChildByName(const string& name);
	//删除自己
	void removeSelf();

	//设置锚点
	void setAnchorPos(const D3DXVECTOR3& v) { m_vAnchorPos = v; }
	void setAnchorPos(float x, float y, float z) { m_vAnchorPos.x = x; m_vAnchorPos.y = y; m_vAnchorPos.z = z; }
	//获取锚点
	D3DXVECTOR3 getAnchorPos() { return m_vAnchorPos; }

	D3DXCOLOR getColor() { return m_color; }
	void setColor(D3DXCOLOR c) { m_color = c; }

	//设置位置
	virtual void setPosition(const D3DXVECTOR3& v){m_vPos = v;}
	void setPosition(float x, float y, float z) {m_vPos.x = x;m_vPos.y = y;m_vPos.z = z;}
	//设置缩放
	void setScale(const D3DXVECTOR3& v) { m_vScale = v; }
	void setScale(float x, float y, float z) {m_vScale.x = x; m_vScale.y = y;m_vScale.z = z;}
	//设置旋转  欧拉角旋转
	void setRotate(const D3DXVECTOR3& v){m_vRotate = v;}
	void setRotate(float x, float y, float z) { m_vRotate.x = x; m_vRotate.y = y; m_vRotate.z = z; }
	//获取位置
	D3DXVECTOR3 getPosition() { return m_vPos; }
	//获取缩放
	D3DXVECTOR3 getScale() { return m_vScale; }
	//获取旋转
	D3DXVECTOR3 getRotate() { return m_vRotate; }
	//得到父节点
	CNode* getParent() { return mParent; }
	//得到子节点
	CNode* getChildByName(const string& name);
	//得到当前矩阵
	D3DXMATRIX getMatrix() { return m_mMatrix; }
	
	void setVisible(bool b) { isVisible = b; }

	void setName(const string& name) { this->name = name; }

protected:

	virtual void update(float dt);
	virtual void render();

	bool isVisible; //是否显示

	bool isPreRemove; //准备删除 移除标志

	D3DXMATRIX m_mMatrix; //变换矩阵

	D3DXVECTOR3 m_vPos;   //位置
	D3DXVECTOR3 m_vScale; //缩放
	D3DXVECTOR3 m_vRotate;//旋转

	D3DCOLOR	m_color;//颜色
	D3DXVECTOR3 m_vAnchorPos;//锚点

	CNode* mParent;  // 父节点
	map<string, CNode*> mChildren;//子节点

	string name; //名字
};

