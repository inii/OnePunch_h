#pragma once
#include <d3dx9math.h>

//������� �������������
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

	//���ù۲��
	void setLookAt(const D3DXVECTOR3& v) { m_vLookat = v; }
	//��ȡ��ͼ�任����
	D3DXMATRIX getViewMatrix() { return m_mMatView; }
private:

	void calcEyePos();

	float m_fLongitude; //����
	float m_fLatitude;  //γ��
	float m_fDistance;  //����

	D3DXVECTOR3 m_vEye;    //�����λ��  ???
	D3DXVECTOR3 m_vLookat; //�۲��λ��
	D3DXVECTOR3 m_vUp;     //�����������

	float m_fAngle;			//��Ұ�н�
	float m_fAspectRatio;	//��߱�
	float m_fFarZ;			//Զ�������
	float m_fNearZ;			//���������

	D3DXMATRIX m_mMatView; //��ͼ�任����
	D3DXMATRIX m_mProject; //͸��ͶӰ����

	float m_fRate;//������

	LPDIRECT3DDEVICE9 m_pDevice;
};

