#include "Light.h"
#include <d3dx9math.h>

CLight::CLight(D3DLIGHTTYPE type)
{
	nLightId = -1;
	ZeroMemory(&light, sizeof(light));

	light.Type = type;// D3DLIGHT_POINT;

	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Ambient.a = 1.0f;

	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	light.Specular.a = 1.0f;

	//点光源
	if (type == D3DLIGHT_POINT) {
		light.Position = D3DXVECTOR3(0, 0, 0);
		light.Range = 5.0f;
		light.Attenuation2 = 0.5f;
	}

	//方向光
	if (type == D3DLIGHT_DIRECTIONAL) {
		D3DXVECTOR3 v = D3DXVECTOR3(0, -1, 1);
		D3DXVec3Normalize(&v, &v);
		light.Direction = v;
	}
}

CLight::~CLight()
{
}

/*
void CGameApp::setPointLight()
{
D3DLIGHT9 light;
ZeroMemory(&light, sizeof(light));

light.Type = D3DLIGHT_POINT;
light.Diffuse.r = 1.0f;
light.Diffuse.g = 1.0f;
light.Diffuse.b = 1.0f;
light.Diffuse.a = 1.0f;

//light.Ambient.r = 1.0f;
//light.Ambient.g = 1.0f;
//light.Ambient.b = 1.0f;
//light.Ambient.a = 1.0f;

//light.Specular.r = 1.0f;
//light.Specular.g = 1.0f;
//light.Specular.b = 1.0f;
//light.Specular.a = 1.0f;

light.Position = D3DXVECTOR3(-2,2,0);
light.Range = 5.0f;
light.Attenuation2 = 0.5f;

m_pDevice->SetLight(0, &light);
m_pDevice->LightEnable(0, TRUE);
}

void CGameApp::updatePointLight()
{
D3DLIGHT9 light;
m_pDevice->GetLight(0, &light);

D3DXMATRIX mat;
D3DXMatrixIdentity(&mat);
D3DXMatrixRotationY(&mat, D3DX_PI / 90);

D3DXVECTOR3 v;
//向量做矩阵的变换
D3DXVec3TransformCoord(&v, &D3DXVECTOR3(light.Position), &mat);
light.Position = v;
m_pDevice->SetLight(0, &light);
}

void CGameApp::updateDirectLight()
{
D3DLIGHT9 light;
m_pDevice->GetLight(0, &light);

D3DXMATRIX mat;
D3DXMatrixIdentity(&mat);
D3DXMatrixRotationY(&mat, D3DX_PI/90);

D3DXVECTOR3 v;
//向量做矩阵的变换
D3DXVec3TransformCoord(&v, &D3DXVECTOR3(light.Direction), &mat);
light.Direction = v;
m_pDevice->SetLight(0, &light);
}

void CGameApp::setDirectLight()
{
D3DLIGHT9 light;
ZeroMemory(&light, sizeof(light));

light.Type = D3DLIGHT_DIRECTIONAL; //方向光
//设置方向
D3DXVECTOR3 v = D3DXVECTOR3(0, -1, 1);
D3DXVec3Normalize(&v, &v);
light.Direction = v;

light.Diffuse.r = 1.0f;
light.Diffuse.g = 1.0f;
light.Diffuse.b = 1.0f;
light.Diffuse.a = 1.0f;

light.Specular.r = 1.0f;
light.Specular.g = 1.0f;
light.Specular.b = 1.0f;
light.Specular.a = 1.0f;

m_pDevice->SetLight(0, &light);
m_pDevice->LightEnable(0, TRUE);
}
*/