#include "FrameSprite.h"

CFrameSprite::CFrameSprite()
{
	mCurIndex = 0;
	mTimeCount = 0.0f;
}

CFrameSprite::~CFrameSprite()
{
}

//"framesprite\bomb\image_%d.png"
void CFrameSprite::init(const string& path, int frame, bool loop, float hz)
{
	mMaxIndex = frame;
	mIntervalTime = 1.0f/hz;
	mLoop = loop;

	char strbuf[255];
	for (int i = 1; i <= frame;i++) {
		sprintf(strbuf, path.c_str(), i);
		CTexture* p = CTextureCache::getInstance().createTexture(strbuf);

		mFrame.push_back(p);
	}
}

void CFrameSprite::update(float dt)
{
	CNode::update(dt);

	mTimeCount += dt;

	if (mTimeCount > mIntervalTime) {
		mCurIndex++;
		mTimeCount = 0.0f;

		if (mCurIndex >= mMaxIndex) {
			if (mLoop)
				mCurIndex = 0;
			else {
				removeSelf();
				return;
			}
		}
	}

	mTexture = mFrame[mCurIndex];
}