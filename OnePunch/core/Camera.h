#pragma once
#include <d3dx9math.h>

//摄像机类 基本摄像机操作
class CCamera
{
	CCamera();
public:
	static CCamera& getInstance() {
		static CCamera s;
		return s;
	}

	~CCamera();

	void update();
	void render();

	D3DXVECTOR3 getEyePos() { return m_vEye; }
	D3DXVECTOR3 getLookat() { return m_vLookat; }
	D3DXVECTOR3 getUp() {return m_vUp;}

	//设置观察点
	void setLookAt(const D3DXVECTOR3& v) { m_vLookat = v; }
	//获取视图变换矩阵
	D3DXMATRIX getViewMatrix() { return m_mMatView; }
private:

	void calcEyePos();

	float m_fLongitude; //经度
	float m_fLatitude;  //纬度
	float m_fDistance;  //距离

	D3DXVECTOR3 m_vEye;    //摄像机位置  ???
	D3DXVECTOR3 m_vLookat; //观察点位置
	D3DXVECTOR3 m_vUp;     //摄像机正方向

	float m_fAngle;			//视野夹角
	float m_fAspectRatio;	//宽高比
	float m_fFarZ;			//远截面距离
	float m_fNearZ;			//近截面距离

	D3DXMATRIX m_mMatView; //视图变换矩阵
	D3DXMATRIX m_mProject; //透视投影矩阵

	float m_fRate;//灵敏度

	LPDIRECT3DDEVICE9 m_pDevice;
};

