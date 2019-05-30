//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: AnimationSetting
//							  Date: 13/7/2009
//******************************************************************************************

#include "AnimationSetting.h"

AnimationSetting::AnimationSetting():m_bBackToIdle(false), m_bLoop(false), m_iNumFrames(0), m_iStartFrame(0), m_sAnimationName(_T("default")), m_bPlay(false)
{

}
AnimationSetting::~AnimationSetting(){

}

const tstring& AnimationSetting::GetAnimationName() const
{
	return m_sAnimationName;
}

void AnimationSetting::SetAnimationName( const tstring& name )
{
	m_sAnimationName = name;
}

int AnimationSetting::GetNumFrames() const
{
	return m_iNumFrames;
}

void AnimationSetting::SetNumFrames( int numframes )
{
	m_iNumFrames = numframes;
}

int AnimationSetting::GetStartFrame() const
{
	return m_iStartFrame;
}

int AnimationSetting::GetRow() const
{
	return m_iRow;
}

void AnimationSetting::SetStartFrame( int startframe )
{
	m_iStartFrame = startframe;
}

bool AnimationSetting::GetLoop() const
{
	return m_bLoop;
}

void AnimationSetting::SetLoop( bool loop )
{
	m_bLoop = loop;
}

bool AnimationSetting::GetBackToIdle() const
{
	return m_bBackToIdle;
}

void AnimationSetting::SetBackToIdle( bool idle )
{
	m_bBackToIdle = idle;
}

void AnimationSetting::SetPlay( bool play )
{
	m_bPlay = play;
}

bool AnimationSetting::GetPlay() const
{
	return m_bPlay;
}

void AnimationSetting::SetRow( int row )
{
	m_iRow = row;
}