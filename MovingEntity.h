//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: MovingEntity
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef MOVINGENTITY_H_INCLUDED
#define MOVINGENTITY_H_INCLUDED


class CharacterSetting;
class AnimationState;
class AnimationSetting;
#include "Vector2D.h"
#include "BaseEntity.h"
#include "AnimationState.h"


enum EnumMovingTypes
{
	HERO = 0,
	BUBBLE = 1,
	ENEMY = 2
};

class MovingEntity : public BaseEntity
{

public:
	MovingEntity(CharacterSetting* setting, double xPos, double yPos, EnumMovingTypes type);
	virtual ~MovingEntity();

	virtual bool Draw();
	virtual bool Tick(float dTime);
	virtual void Init();
	virtual void SpecialEntityChecks(float dTime){};

	void SetAnimationState(EnumAnimationStates state);
	void SetIdle();
	bool GetJumping() const;
	bool GetIdle() const;
	bool GetIdleReset() const;
	bool GetAlive() const;
	void Jump( );
	void StopJumping();

	const Vector2D& GetAccleration() const;
	const Vector2D& GetOldPosition() const;
	const Vector2D& GetPosition() const;
	const Vector2D& GetCurrentSpeed() const;

	RECT GetRect() const;

	void ToggleCollisionDebug();
	void ToggleCollision();

	virtual void Kill();

	int GetType() const;
	bool GetDying() const;

	virtual void MoveLeft(float dt);
	virtual void MoveRight(float dt);


	
protected:
	
	void InitAnimation(float spritestartX, float spritestartY, int numframes);
	void SetDefaultAnimation();
	void LoadAnimation(const tstring& animationname);
	void UpdatePosition(float dTime);
	void ResetSpeed();
	void SwitchSpeed(bool isLeft);
	virtual void FallDown();
	void GoDown(float dTime);

	float m_Speed;

	bool m_bLeft;
	bool m_bJump;
	bool m_bIdleReset;
	bool m_bPaused;
	bool m_bCheckCollision;

	Vector2D m_vForce;
	Vector2D m_vMaxSpeed;
	Vector2D m_vAcceleration;
	Vector2D m_vCurrentSpeed, m_vOldSpeed;
	Vector2D m_vOldPosition;
	Vector2D m_vSpawnPosition;

	CharacterSetting* m_pSettings;
	hgeAnimation* m_pAnim;

	AnimationState* m_pAnimationState;
	EnumAnimationStates m_lastAnimationState;
	const AnimationSetting* m_pCurrentAnimationSettings;

	float m_fCurrentRenderTime;
	float m_fTotalRenderTime;
	float m_fCurrentDieTime;
	float m_fTotalDieTime;
	bool m_bAlive;
	bool m_bDying;
	int m_iLives;
	int m_Type;

private:
	bool m_bCollisionDebug;
	MovingEntity(const MovingEntity& t);
	MovingEntity& operator=(const MovingEntity& t);
	void SetJumping();
	void CheckLives();
	void ResetValues();
	void MoveToNewSpawnPlace(float dTime);

};

#endif