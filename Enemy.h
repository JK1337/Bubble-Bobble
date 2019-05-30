//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Enemy
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "MovingEntity.h"
class Hero;
class EnemyBehavior;

class Enemy : public MovingEntity {

public:
	Enemy(CharacterSetting* setting, double xPos, double yPos, EnumMovingTypes type);
	virtual ~Enemy();
	virtual void RegisterHero(const Hero* hero);
	virtual void SetBehavior(EnemyBehavior* behavior);
protected:
	virtual void SpecialEntityChecks(float dTime);
	//virtual void SpecialEnemyChecks(float dTime, const Vector2D& enemyposition) = 0;
	EnemyBehavior* m_pEnemyBehavior;
	const Hero* m_pCurrentLockedHero;

private:
	//const std::vector<Hero*> m_vHeros;
	
	Enemy(const Enemy& t);
	Enemy& operator=(const Enemy& t);
};

#endif