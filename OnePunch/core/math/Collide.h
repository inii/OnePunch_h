#pragma once
#include <d3dx9math.h>

//显示区
struct CRect
{
	float left;
	float top;
	float right;
	float bottom;
};

//碰撞区
struct CCollide
{
	float left;
	float top;
	float right;
	float bottom;

	CCollide() {
		left   = 0;
		top    = 0;
		right  = 0;
		bottom = 0;
	}

	//两个碰撞区是否碰撞
	static bool isCollide(CCollide& c1, CCollide& c2) {
		if (c1.right > c2.left && c1.left < c2.right && c1.bottom > c2.top && c1.top < c2.bottom)
			return true;
		return false;
	}

	//一个点跟碰撞区是否碰撞
	static bool isCollide(const D3DXVECTOR2& v, CCollide& c2) {
		if (v.x > c2.left && v.x < c2.right && v.y > c2.top && v.y < c2.bottom)
			return true;
		return false;
	}
};

