//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: AnimationSetting
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef ANIMATIONSETTING_H_INCLUDED
#define ANIMATIONSETTING_H_INCLUDED


#include "stdafx.h"

class AnimationSetting {
public:
	AnimationSetting();
	virtual ~AnimationSetting();
	
	const tstring& GetAnimationName() const;
	void SetAnimationName(const tstring& name);

	int GetNumFrames() const;
	void SetNumFrames(int numframes);

	int GetStartFrame() const;
	void SetStartFrame(int startframe);

	bool GetLoop() const;
	void SetLoop(bool loop);

	bool GetBackToIdle() const;
	void SetBackToIdle(bool idle);

	bool GetPlay() const;
	void SetPlay(bool play);

	int GetRow() const;
	void SetRow(int row);
private:

	tstring			m_sAnimationName;
	int				m_iStartFrame;
	int				m_iNumFrames;
	int				m_iRow;
	bool			m_bLoop;
	bool			m_bBackToIdle;
	bool			m_bPlay;


	AnimationSetting(const AnimationSetting& t);
	AnimationSetting& operator=(const AnimationSetting& t);
};

#endif