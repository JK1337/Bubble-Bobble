//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: MovingEntity
//							  Date: 10/7/2009
//******************************************************************************************

#include "stdafx.h"

#include "MovingEntity.h"
#include "CharacterSetting.h"
#include "SpriteSheetSetting.h"
#include "AnimationSetting.h"
#include "AnimationState.h"
#include "Vector2D.h"
#include "CollisionMap.h"
#include "MyGameDefines.h"
#include "EntityManager.h"
#include "StateManager.h"
MovingEntity::MovingEntity(CharacterSetting* setting, double xPos, double yPos, EnumMovingTypes type):
														BaseEntity(xPos, yPos, setting->GetSpriteSheetSetting()->GetWidth(), setting->GetSpriteSheetSetting()->GetHeight()), 
														m_Speed(0), m_vOldSpeed(0,0), m_vCurrentSpeed(0,0), m_vOldPosition(150.0,150.0),
														m_vAcceleration(20, -550), m_vForce(0, 1850), m_vMaxSpeed(150, -950),
														m_pSettings(setting), m_pAnim(0),
														m_bLeft(false), m_bJump(false), m_pAnimationState(new AnimationState()),
														m_fCurrentRenderTime(0), m_fTotalRenderTime(0), m_bIdleReset(false),
														m_bPaused(false), m_bCollisionDebug(false), m_bAlive(true), m_bDying(false), m_Type(type), m_bCheckCollision(true), m_iLives(0),m_vSpawnPosition(xPos,yPos)
{

}
MovingEntity::~MovingEntity()
{
	
}

void MovingEntity::Init()
{
	LoadTexture("Characters/" + m_pSettings->GetName() + ".png");
	SetDefaultAnimation();	
}

void MovingEntity::SetDefaultAnimation()
{
	//InitAnimation(m_pSettings->GetName() + _T(".png"), m_pSettings->)	
	LoadAnimation(m_pSettings->GetStartAnimation());
}


void MovingEntity::LoadAnimation(const tstring& animationname)
{
	if(!m_bDying)
	{
		m_pCurrentAnimationSettings = m_pSettings->GetAnimationByName(animationname);
		float spritestartX = m_pCurrentAnimationSettings->GetStartFrame()*
			m_pSettings->GetSpriteSheetSetting()->GetWidth();
		int spriteRow = m_pCurrentAnimationSettings->GetRow();
		float spritestartY = spriteRow*m_pSettings->GetSpriteSheetSetting()->GetHeight();
		InitAnimation(spritestartX, spritestartY, m_pCurrentAnimationSettings->GetNumFrames());
	}else
	{
		//soms krijgen we problemen als we nog keys ingedrukt hebben
		//en naar die switchen, daarom deze extra check
		if(!(m_pAnimationState->GetAnimationState() == DIE))
		{
			m_pCurrentAnimationSettings = m_pSettings->GetAnimationByName(_T("die"));
			float spritestartX = m_pCurrentAnimationSettings->GetStartFrame()*
				m_pSettings->GetSpriteSheetSetting()->GetWidth();
			//float spritestartX = 0;
			int spriteRow = m_pCurrentAnimationSettings->GetRow();
			float spritestartY = spriteRow*m_pSettings->GetSpriteSheetSetting()->GetHeight();
			InitAnimation(spritestartX, spritestartY, m_pCurrentAnimationSettings->GetNumFrames());
		}
	}
}

void MovingEntity::InitAnimation(float spritestartX, float spritestartY, int numframes)
{
	m_bIdleReset = false;

	float framespersecond(10);
	//delete old if necessairy
	if(m_pAnim != NULL)
	{
		delete m_pAnim;
	}

	//animation inladen met onze vars
	m_pAnim=new hgeAnimation(m_Tex, numframes, framespersecond, spritestartX, spritestartY, m_pSettings->GetSpriteSheetSetting()->GetWidth(), m_pSettings->GetSpriteSheetSetting()->GetHeight());

	if(m_pCurrentAnimationSettings->GetBackToIdle())
	{
			m_fTotalRenderTime = numframes * (1.0f/framespersecond);
			m_fCurrentRenderTime = 0.0f;
		
	}else
	{
		m_bIdleReset = true;
	}
	
	//filterkleurke pakken indien nodig
	//m_pAnim->SetColor(0xFFFFA000);
	//"hotspot" zetten -> plaats waar focus ligt, middenplek
	m_pAnim->SetHotSpot(m_pSettings->GetSpriteSheetSetting()->GetMidX(), m_pSettings->GetSpriteSheetSetting()->GetMidY());
	if(m_bLeft)
		m_pAnim->SetFlip(true, false, false);
	//spelen maar...
	if(m_pCurrentAnimationSettings->GetPlay())
		m_pAnim->Play();
}



bool MovingEntity::Draw()
{
	if(m_bAlive)
	{
		m_pAnim->Render(static_cast<float>(m_vPosition.x), static_cast<float>(m_vPosition.y));

		RECT rect = GetRect();

		if(m_bCollisionDebug)
		{
			GAME_ENGINE->Gfx_RenderLine(	static_cast<float>(rect.left), 	static_cast<float>(rect.top), 	static_cast<float>(rect.right), 	static_cast<float>(rect.top),
				0xFFFFFFFF, 0.1f);
			GAME_ENGINE->Gfx_RenderLine( static_cast<float>(rect.left), 	static_cast<float>(rect.bottom), 	static_cast<float>(rect.right), 	static_cast<float>(rect.bottom), 0xFFFFFFFF, 0.1f);
			GAME_ENGINE->Gfx_RenderLine(static_cast<float>(rect.left), 	static_cast<float>(rect.top), 	static_cast<float>(rect.left), 	static_cast<float>(rect.bottom), 0xFFFFFFFF, 0.1f);
			GAME_ENGINE->Gfx_RenderLine( static_cast<float>(rect.right), 	static_cast<float>(rect.top), 	static_cast<float>(rect.right), 	static_cast<float>(rect.bottom), 0xFFFFFFFF, 0.1f);
		}

		//m_pAnim->RenderStretch(m_vPosition.x, m_vPosition.y, m_vPosition.x + (m_pSettings->GetSpriteSheetSetting()->GetWidth()*2), m_vPosition.y + (m_pSettings->GetSpriteSheetSetting()->GetHeight()*2));
		return false;
	}else
	{
		EntityManager::GetSingleton()->RegisterDeadEntity(this);
		return false;
	}
}

void MovingEntity::ResetSpeed()
{
	m_vOldSpeed.Zero();
	m_vCurrentSpeed.Zero();
}

bool MovingEntity::Tick(float dTime)
{
	if(StateManager::GetSingleton()->GetGameState() == STARTED || StateManager::GetSingleton()->GetGameState() == LEVELENDING)
	{
		SpecialEntityChecks(dTime);
		//HandleKeyEvents(dTime);
		//if(m_pSettings->)
		//if(m_pCurrentAnimationSettings->GetBackToIdle() && m_pAnim->P)
		if(m_pCurrentAnimationSettings->GetBackToIdle())
		{
			m_fCurrentRenderTime += dTime;

			if(m_fCurrentRenderTime > m_fTotalRenderTime)
			{
				if(!m_bJump)
					SetIdle();
				else
					SetJumping();
				//else()
			}
		}

		m_pAnim->Update(dTime);

		switch(m_pAnimationState->GetAnimationState())
		{
		case IDLE:

			break;

		case WALK:
			UpdatePosition(dTime);
			break;

		case ATTACK:
			if(m_bJump)
				UpdatePosition(dTime);
			break;

		case JUMP:
			UpdatePosition(dTime);
			break;

		case DIE:
			GoDown(dTime);
			break;

		case TRANSITION:
			MoveToNewSpawnPlace(dTime);
		break;
		}

		if(m_bCheckCollision)
		{
			Vector2D moveback = CollisionMap::GetSingleton()->CheckCollision(GetRect(), this);
			if(moveback.y == -10000)
			{
				//val naar beneden geen grondvlak ontdekt
				FallDown();

			}else{
				m_vPosition -= moveback;
			}
		}
	}

	return false;
}

void MovingEntity::MoveToNewSpawnPlace(float dTime)
{
	//float fMoveTime(2.0f);
	//m_vPosition.x 
	
	Vector2D vCurrentSpeed(250.0f, 250.0f);


	//eerst de ybewegen
	if(!(m_vPosition.y == m_vSpawnPosition.y))
	{
		m_vPosition.y += vCurrentSpeed.y * dTime;
		if(m_vPosition.y > m_vSpawnPosition.y)
		{
			m_vPosition.y = m_vSpawnPosition.y;
		}
	}else
	{
		//daarna de xbewegen

		bool bFinished(false);
		if(m_vPosition.x > m_vSpawnPosition.x)
		{
			m_vPosition.x -= vCurrentSpeed.x * dTime;
			if(m_vPosition.x < m_vSpawnPosition.x)
			{
				m_vPosition.x = m_vSpawnPosition.x;
				bFinished = true;
			}
		}else
		{
			m_vPosition.x += vCurrentSpeed.x * dTime;
			if(m_vPosition.x > m_vSpawnPosition.x)
			{
				m_vPosition.x = m_vSpawnPosition.x;
				bFinished = true;
			}
		}

		if(bFinished)
		{
			ToggleCollision();
			StateManager::GetSingleton()->SetGameState(STARTED);
		}
	}	
}

void MovingEntity::ToggleCollision()
{
	m_bCheckCollision = !m_bCheckCollision;
}

void MovingEntity::FallDown()
{
	m_bJump = true;
	//todo falldown animation state maken
	m_pAnimationState->SetAnimationState(JUMP);
}

void MovingEntity::GoDown(float dTime)
{
	Vector2D vCurrentSpeed(0, 250.0f);
	m_vPosition += vCurrentSpeed * dTime;	

	if(m_vPosition.y > GameManager::GetSingleton()->GetScreenHeight() + 20)
	{
		CheckLives();
	}
}

void MovingEntity::ResetValues()
{
	SetIdle();
	m_bCheckCollision = true;
	m_bDying = false;
	m_bAlive = true;
	m_vPosition = m_vSpawnPosition;
	SetDefaultAnimation();
	m_pAnimationState->SetAnimationState(IDLE);
	ResetSpeed();
	m_bJump = false;
}

void MovingEntity::CheckLives()
{
	if(m_iLives > 0)
	{
		--m_iLives;
		ResetValues();
	}
	else
	{
		//ENDGAME
		StateManager::GetSingleton()->SetGameState(GAMEOVER);
		m_bAlive = false;
		int endgame = 1;
	}
}


RECT MovingEntity::GetRect() const
{
	RECT rect;
	/*
	rect.left = m_vPosition.x - 15;
	rect.right = rect.left +  m_dWidth - 30;
	rect.top = m_vPosition.y + 15 ;
	rect.bottom = rect.top + m_dHeight - 30;
	*/ 

	rect.left = static_cast<LONG>(m_vPosition.x - 22.5);
	rect.right =  static_cast<LONG>(m_vPosition.x + 22.5);
	rect.top =  static_cast<LONG>(m_vPosition.y - 22.5);
	rect.bottom =  static_cast<LONG>(m_vPosition.y + 22.5);
	return rect;
}

void MovingEntity::UpdatePosition(float dTime)
{
	m_vOldSpeed = m_vCurrentSpeed;
	m_vOldPosition = m_vPosition;
	
	Vector2D vTotAcceleration(0,0);

	if (m_pAnimationState->GetAnimationState() == WALK)
	{
		//doe de walk
		//vTotAcceleration.x = m_v
	}

	else  if(m_bJump)
	{
		//bereken de versnelling ten gevolge van de force (enkel bij jumping
		vTotAcceleration = m_vForce;
	}

	//Check collision en rollback indien nodig
      	m_vPosition += m_vCurrentSpeed * dTime + vTotAcceleration * dTime * dTime / 2;
		m_vCurrentSpeed += vTotAcceleration * dTime;

	float halfheight = m_pAnim->GetHeight()/2.0f;
	float halfwidth = m_pAnim->GetWidth()/2.0f;
	if(m_vPosition.y + halfheight > 1024 )
	{
		m_vPosition.y = 1024 - halfheight;
		if(m_bJump)
			StopJumping();
	}

	if(m_vPosition.y - halfheight < 0)
	{
		m_vPosition.y = halfheight;	
		if(m_bJump)
			StopJumping();
	}

	if(m_vPosition.x - halfwidth < 0)
	{
		m_vPosition.x = halfwidth;
		
	}

	if(m_vPosition.x + halfwidth > 1024)
	{
		m_vPosition.x = 1024-halfwidth;
	
	}
}


void MovingEntity::SetIdle()
{
	LoadAnimation(_T("idle"));
	m_pAnimationState->SetAnimationState(IDLE);
}

bool MovingEntity::GetIdle() const
{
	if(m_pAnimationState->GetAnimationState() == IDLE)
		return true;
	else
		return false;
}

void MovingEntity::SwitchSpeed( bool isLeft )
{
	if(isLeft)
		m_vCurrentSpeed.x = -m_vMaxSpeed.x;
	else
		m_vCurrentSpeed.x = m_vMaxSpeed.x;
}

bool MovingEntity::GetJumping() const
{
	return m_bJump;
}

bool MovingEntity::GetIdleReset() const
{
	return m_bIdleReset;
}

void MovingEntity::Jump()
{
	this->LoadAnimation(_T("jump"));
	m_bJump = true;
	ResetSpeed();
	m_vCurrentSpeed.y = m_vMaxSpeed.y;
	m_pAnimationState->SetAnimationState(JUMP);
}

void MovingEntity::StopJumping()
{
	
	m_vCurrentSpeed.y = 0;
	//m_vAcceleration.y = 0;
	m_bJump = false;
	if(m_vCurrentSpeed.x != 0)
	{
		m_pAnimationState->SetAnimationState(WALK);
		this->LoadAnimation(_T("walk"));
	}else
	{
		m_pAnimationState->SetAnimationState(IDLE);
		this->LoadAnimation(_T("idle"));
	}

}

void MovingEntity::SetJumping()
{
	this->LoadAnimation(_T("jump"));
	m_pAnimationState->SetAnimationState(JUMP);
	m_bJump = true;
	//m_vCurrentSpeed.y = m_vMaxSpeed.y;
}

const Vector2D& MovingEntity::GetAccleration() const
{
	return m_vAcceleration;
}

const Vector2D& MovingEntity::GetOldPosition() const
{
	return m_vOldPosition;
}

const Vector2D& MovingEntity::GetPosition() const
{
	return m_vPosition;
}

void MovingEntity::ToggleCollisionDebug() 
{
	m_bCollisionDebug = true;
}

bool MovingEntity::GetAlive() const
{
	return m_bAlive;
}

int MovingEntity::GetType() const
{
	return m_Type;
}

bool MovingEntity::GetDying() const
{
	return m_bDying;
}

const Vector2D& MovingEntity::GetCurrentSpeed() const
{
	return m_vCurrentSpeed;
}

void MovingEntity::MoveLeft( float dt )
{
	SwitchSpeed(true);

	if(!m_bLeft)
	{

		m_bLeft = true;

		if(!m_bJump)
		{
			this->LoadAnimation(_T("walk"));
		}else
		{
			m_pAnim->SetFlip(true, false, false);
		}

		//m_pAnim->SetFlip(true, false, false);
	}



	if(!m_bJump)
	{
		if(m_pAnimationState->GetAnimationState() != WALK)
		{
			this->LoadAnimation(_T("walk"));
			m_pAnimationState->SetAnimationState(WALK);
		}
	}		
}

void MovingEntity::MoveRight( float dt )
{
	SwitchSpeed(false);

	if(m_bLeft)
	{
		m_bLeft = false;

		if(!m_bJump)
		{
			this->LoadAnimation(_T("walk"));
		}else
		{
			m_pAnim->SetFlip(false, false, false);
		}

		//m_pAnim->SetFlip(false, false, false);
	}

	if(!m_bJump)
	{
		if(m_pAnimationState->GetAnimationState() != WALK)
		{
			this->LoadAnimation(_T("walk"));
			m_pAnimationState->SetAnimationState(WALK);
		}
	}
}

void MovingEntity::Kill()
{
	m_bDying = true;
	m_bAlive = false;
}

void MovingEntity::SetAnimationState(EnumAnimationStates state)
{
	m_pAnimationState->SetAnimationState(state);
}


