//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: AnimationState
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef ANIMATIONSTATE_H_INCLUDED
#define ANIMATIONSTATE_H_INCLUDED


#include "stdafx.h"

enum EnumAnimationStates
{
	IDLE = 0,
	WALK = 1,
	ATTACK = 2,
	JUMP = 3,
	DIE = 4,
	CAPTURE = 5,
	TRANSITION = 6
};

class AnimationState {
public:
	
	AnimationState();
	virtual ~AnimationState();
	void SetAnimationState(EnumAnimationStates animstate);
	EnumAnimationStates GetAnimationState();

private:
	EnumAnimationStates m_CurrentAnimationState;
	AnimationState(const AnimationState& t);
	AnimationState& operator=(const AnimationState& t);
	
};

#endif