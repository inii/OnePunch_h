#pragma once
#include <d3d9.h>
//光源
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

	//设置位置

	//设置方向


	//启用后的灯光id 未启用默认为-1
	int nLightId;

private:
	D3DLIGHT9 light;
};

