//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Bubble
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef BUBBLE_H_INCLUDED
#define BUBBLE_H_INCLUDED

#include "MovingEntity.h"
#include "Vector2D.h"

class Bubble : public MovingEntity
{
public:
	Bubble(CharacterSetting* charsetting, double xPos, double yPos, bool direction, EnumMovingTypes type);
	virtual ~Bubble();
	virtual bool Tick(float dTime);
	virtual void UpdatePosition(float dTime);
	bool HandleEnemies();
	bool HandleJump();
	virtual void Kill();
	void CaptureMode();
	bool GetCaptured();
	
private:
	bool m_bGoingUp, m_bToIdlePosition, m_bFinished, m_bCaptured;
	float m_fShootTime, m_fTotalShootTime;
	Vector2D m_vRandomOffset;
	Bubble(const Bubble& t);
	Bubble& operator=(const Bubble& t);
	void RefreshAnimation(float dTime);
	void GoUp();
};

#endif