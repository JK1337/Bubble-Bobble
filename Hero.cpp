//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Hero
//							  Date: 10/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "Hero.h"
#include "CharacterSetting.h"
#include "AnimationState.h"
#include "EntityManager.h"
#include "StateManager.h"

Hero::Hero(CharacterSetting* settings,double xPos, double yPos, EnumMovingTypes type):MovingEntity(settings,xPos,yPos,type), m_bAttacking(false), m_fCurrentAttackTime(0), m_fTotalAttackTime(0.25f)
{
	m_iLives = 2;
}

Hero::~Hero()
{

}



void Hero::Attack(  )
{
	if(!m_bAttacking)
	{
		m_bAttacking = true;
		m_fCurrentAttackTime = 0;
		this->LoadAnimation(_T("attack"));

		//if(!m_bJump)
		//	ResetSpeed();
		//na attack moeten we terug switchen naar de animatie dat bezig was
		m_lastAnimationState = m_pAnimationState->GetAnimationState();
		m_pAnimationState->SetAnimationState(ATTACK);
		EntityManager::GetSingleton()->CreateBubble(static_cast<float>(m_vPosition.x), static_cast<float>(m_vPosition.y), m_bLeft);
	}

}

void Hero::SpecialEntityChecks(float dTime)
{
	if(!m_bDying && m_bAlive)
	{
		if(m_bAttacking)
		{
			m_fCurrentAttackTime += dTime;
			if(m_fCurrentAttackTime > m_fTotalAttackTime)
			{
				m_bAttacking = false;
			}
		}

	//eerste checken voor bubbles
	
		bool bHaveToJump = EntityManager::GetSingleton()->HeroBubbleCollision(this);
		if(bHaveToJump)
		{
			this->Jump();
		}

		//dan checken voor enemies
		bool bHaveToDie = EntityManager::GetSingleton()->HeroEnemyCollision(this);
		if(bHaveToDie)
		{
			this->Kill();
		}
	}
	
}

void Hero::Kill()
{
	OutputDebugStringW(_T("-die-"));
	m_bDying = true;
	this->LoadAnimation(_T("die"));
	m_pAnimationState->SetAnimationState(DIE);
	ToggleCollision();
	//GAME_ENGINE
}

void Hero::PrepareForNewLevel( const Vector2D& position )
{
	LoadAnimation(_T("transition"));
	SetAnimationState(TRANSITION);
	SetSpawnPosition(position);
}

void Hero::SetSpawnPosition(const Vector2D& spawnposition)
{
	m_vSpawnPosition = spawnposition;
}