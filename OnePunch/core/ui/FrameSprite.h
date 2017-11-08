#pragma once
#include <string>
#include <vector>
#include "Sprite.h"
using namespace std;

//帧动画
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

	float mSpeed; //最高支持3倍
	int mCurIndex; //当前运行到第几帧
	int mMaxIndex; //最大帧数

	float mTimeCount;
	float mIntervalTime;

	bool mLoop; //是否循环
};

