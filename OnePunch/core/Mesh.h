#pragma once
#include "node.h"

class CMesh : public CNode
{
	CMesh();
public:
	~CMesh();

	static CMesh* create() {
		return new CMesh;
	}

	void update(float dt);
	void render();

private:
	float mMoveSpeed;
	ID3DXMesh* mpMesh;
};

