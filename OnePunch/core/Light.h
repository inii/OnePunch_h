#pragma once
#include <d3d9.h>
//��Դ
class CLight
{
	CLight(D3DLIGHTTYPE type);
public:
	~CLight();

	static CLight* create(D3DLIGHTTYPE type) {
		CLight* light = new CLight(type);
		return light;
	}

	D3DLIGHT9 getLight() { return light; }

	//����λ��

	//���÷���


	//���ú�ĵƹ�id δ����Ĭ��Ϊ-1
	int nLightId;

private:
	D3DLIGHT9 light;
};

