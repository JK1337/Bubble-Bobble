//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Bubble
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "Bubble.h"
#include "AnimationSetting.h"
#include "GameManager.h"
#include "EntityManager.h"
Bubble::Bubble(CharacterSetting* charsetting, double xPos, double yPos, bool directionleft,EnumMovingTypes type):MovingEntity(charsetting,xPos,yPos, type), 
								m_fShootTime(0), m_fTotalShootTime(.5f), m_bGoingUp(false), m_bToIdlePosition(false), m_bFinished(false),m_bCaptured(false)
{
	//todo haal hier uit fix base classe
	if(directionleft)
	{
		m_vMaxSpeed.x = -225;
		
	}else
	{
		m_vMaxSpeed.x = 225;
	}

	m_vCurrentSpeed.x = m_vMaxSpeed.x;

	//we geven random offset mee zodat ze niet allemaal op dezelfde eindpositie aankomen
	float maxoffset = 10;
	m_vRandomOffset.x =  ((rand() % 10 + 1)-5) * maxoffset;
	m_vRandomOffset.y = ((rand() % 10 + 1)-5) * maxoffset;
}


Bubble::~Bubble()
{

}

bool Bubble::Tick(float dTime)
{
	if(!m_bPaused)
		m_pAnim->Update(dTime);

	if(!m_bFinished && !m_bDying)
	{
		RefreshAnimation(dTime);

		UpdatePosition(dTime);

		m_fShootTime += dTime;

		if(!m_bGoingUp)
		{
			if(m_fShootTime > m_fTotalShootTime)
			{
				//switch state
				GoUp();
			}
		}
	}
	else if(m_bDying)
	{
		RefreshAnimation(dTime);
		m_fCurrentDieTime += dTime;
		if(m_fCurrentDieTime > m_fTotalDieTime)
		{
			m_bAlive = false;
		}
	}

	m_pAnim->Update(dTime);

	return false;
}

void Bubble::GoUp()
{
	m_bGoingUp = true;
	m_vCurrentSpeed.y = -75;
	m_pAnimationState->SetAnimationState(IDLE);
	//this->SetAnimationState()
	LoadAnimation(_T("idle"));
}

void Bubble::RefreshAnimation(float dTime)
{
	if(!m_pCurrentAnimationSettings->GetLoop() && !m_bPaused)
	{
		m_fCurrentRenderTime += dTime;

		if(m_fCurrentRenderTime > m_fTotalRenderTime)
		{
			m_bPaused = true;
			m_pAnim->SetFrame(m_pAnim->GetFrames());
		}
	}
}

bool Bubble::HandleEnemies()
{
	//als we nog niet naar boven gaan kunnen we enemies raken met deze bubble
	if(!m_bGoingUp && !m_bCaptured)
		return true;
	else
		return false;
}



void Bubble::UpdatePosition(float dTime)
{

	if(!m_bToIdlePosition)
	{
//just fired or going up
		if(!m_bGoingUp)
		{
			m_vOldSpeed = m_vCurrentSpeed;
			m_vOldPosition = m_vPosition;

			m_vPosition += m_vCurrentSpeed * dTime;
		}else
		{
			//going up
			m_vPosition.y += m_vCurrentSpeed.y * dTime;
			if(m_vPosition.y + m_vRandomOffset.y < 150)
			{
				m_bToIdlePosition = true;
			}
		}
	}else{
//to idle position
		//go to middle
		if(m_vPosition.x  > GameManager::GetSingleton()->GetScreenWidth()/2.0f)
		{
			//move left
			m_vPosition.x -= abs(m_vMaxSpeed.x)*dTime;
		}else{
			//move right
			m_vPosition.x += abs(m_vMaxSpeed.x)*dTime;
		}
		

		//als we binnen 30 pixels ten opzicht van het midden zijn mogen we volledig stoppen
		if(abs(GameManager::GetSingleton()->GetScreenWidth()/2.0f - m_vPosition.x + m_vRandomOffset.x) < 30)
		{
			//finished
			m_bFinished =true;
		}
	}


	//m_vCurrentSpeed += vTotAcceleration * dTime;
}


void Bubble::Kill()
{
	//we use shoottime to save variables
	m_fCurrentDieTime = 0;
	m_fTotalDieTime = 2.0f;

	//switch animation states
	m_pAnimationState->SetAnimationState(DIE);
	LoadAnimation(_T("die"));

	m_bDying = true;

	if(m_bCaptured)
		EntityManager::GetSingleton()->DropPresent(m_vPosition);
}

bool Bubble::HandleJump()
{
	if(((!m_bDying) && m_bAlive))
		return (m_bGoingUp);
	else
		return false;
}

void Bubble::CaptureMode()
{
	GoUp();
	m_bCaptured = true;
	//m_pAnimationState->SetAnimationState(CAPTURE);
	LoadAnimation(_T("capture"));
	//m_bToIdlePosition = true;
}

bool Bubble::GetCaptured()
{
	return m_bCaptured;
}