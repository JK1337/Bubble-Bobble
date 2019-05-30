//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Hero
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

class CharacterSetting;

#include "MovingEntity.h"


class Hero: public MovingEntity
{
public:
	Hero(CharacterSetting* setting, double xPos, double yPos, EnumMovingTypes type);
	virtual ~Hero();

	virtual void Attack();
	virtual void SpecialEntityChecks(float dTime);
	virtual void Kill();
	virtual void PrepareForNewLevel(const Vector2D& position);

protected:
	

private:
	void SetSpawnPosition(const Vector2D& spawnposition);
	float m_fCurrentAttackTime;
	float m_fTotalAttackTime;
	bool m_bAttacking;
	Hero(const Hero& t);
	Hero& operator=(const Hero& t);

};

#endif