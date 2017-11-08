#pragma once
#include <string>
#include <vector>
#include "Sprite.h"
using namespace std;

//֡����
class CFrameSprite : public CSprite
{
	CFrameSprite();
public:
	~CFrameSprite();

	static CFrameSprite* create(const string& path, int frame, bool loop=false, float hz=24.0f)
	{
		CFrameSprite * p = new CFrameSprite();
		p->init(path, frame, loop, hz);
		return p;
	}

	void init(const string& path, int frame, bool loop, float hz);

	void update(float dt);

	void setHz(float hz) { mIntervalTime = 1.0f / hz; }
private:
	vector<CTexture*> mFrame;

	float mSpeed; //���֧��3��
	int mCurIndex; //��ǰ���е��ڼ�֡
	int mMaxIndex; //���֡��

	float mTimeCount;
	float mIntervalTime;

	bool mLoop; //�Ƿ�ѭ��
};

