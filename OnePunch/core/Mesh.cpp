#include "Mesh.h"
#include "D3DDevice.h"
#include "Terrain.h"
#include "Input.h"
#include "Camera.h"

CMesh::CMesh()
	:mMoveSpeed(1.6f)
{
	auto pDevice = CD3DDevice::getInstance().getDevice();

	LPD3DXBUFFER sphBuff;
	//HRESULT res = D3DXCreateTeapot(pDevice, &mpMesh, &sphBuff);
	//HRESULT res = D3DXCreateSphere(pDevice, 1, 60, 60,&mpMesh, &sphBuff);
	//HRESULT res = D3DXCreateBox(pDevice, 1, 1, 1, &mpMesh, &sphBuff);
	HRESULT res = D3DXCreateCylinder(pDevice, 2, 2, 15,15,5,&mpMesh, &sphBuff);
	if (FAILED(res)) {
		MessageBox(NULL, "创建茶壶失败!", "警告", MB_OK);
		return;
	}
}

CMesh::~CMesh()
{
}

void CMesh::update(float dt)
{
	CNode::update(dt);

	//移动
	D3DXVECTOR3 v = getPosition();

	CInput& input = CInput::getInstance();
	CCamera& camera = CCamera::getInstance();

	D3DXVECTOR3 vEye = camera.getEyePos();
	D3DXVECTOR3 vLook = camera.getLookat();
	D3DXVECTOR3 vUp = camera.getUp();

	D3DXVECTOR3 vDir = vLook - vEye;
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vCross;
	D3DXVec3Cross(&vCross, &vUp, &vDir);

	auto vsp = mMoveSpeed*dt;
	if (input.keyHold(DIK_LSHIFT)) { vsp = mMoveSpeed*3.0f*dt; }

	if (input.keyHold(DIK_W)) { v += (vDir*vsp); }
	if (input.keyHold(DIK_S)) { v -= (vDir*vsp); }
	if (input.keyHold(DIK_A)) { v -= (vCross*vsp); }
	if (input.keyHold(DIK_D)) { v += (vCross*vsp); }

	CTerrain *pTer = (CTerrain*)getParent()->getChildByName("map");
	float y = pTer->getHight(v.x,v.z);
	RECT r = pTer->getRect();
	if (v.x < r.left) v.x = r.left;
	if (v.x > r.right) v.x = r.right;
	if (v.z < r.top) v.z = r.top;
	if (v.z > r.bottom) v.z = r.bottom;

	v.y = y+0.3f;
	setPosition(v);
}

void CMesh::render()
{
	if (!isVisible)return;

	CNode::render();

	auto pDevice = CD3DDevice::getInstance().getDevice();
	pDevice->BeginScene();

	D3DMATERIAL9 material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse.r = 1.0f;
	material.Diffuse.g = 0.0f;
	material.Diffuse.b = 0.0f;
	material.Diffuse.a = 1.0f;

	material.Ambient.r = 1.0f;
	material.Ambient.g = 0.5f;
	material.Ambient.b = 0.5f;
	material.Ambient.a = 1.0f;

	material.Emissive.r = 1.0f;
	material.Emissive.g = 0.3f;
	material.Emissive.b = 0.3f;
	material.Emissive.a = 1.0f;
	pDevice->SetMaterial(&material);

	//material.Specular.r = 1.0f;
	//material.Specular.g = 1.0f;
	//material.Specular.b = 1.0f;
	//material.Specular.a = 1.0f;
	//material.Power = 1.0f;
	//pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTransform(D3DTS_WORLD, &m_mMatrix);

	pDevice->SetTexture(0,NULL);
	mpMesh->DrawSubset(0);

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->EndScene();
}