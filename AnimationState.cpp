//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: AnimationState
//							  Date: 13/7/2009
//******************************************************************************************

#include "AnimationState.h"


AnimationState::AnimationState(){
	m_CurrentAnimationState = IDLE;
}
AnimationState::~AnimationState(){

}

void AnimationState::SetAnimationState( EnumAnimationStates animstate )
{
	m_CurrentAnimationState = animstate;
}

EnumAnimationStates AnimationState::GetAnimationState()
{
	return m_CurrentAnimationState;
}