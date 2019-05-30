//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Enemy
//							  Date: 10/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "Enemy.h"
#include "EnemyBehavior.h"
#include "Hero.h"

Enemy::Enemy(CharacterSetting* setting, double xPos, double yPos, EnumMovingTypes type):MovingEntity(setting, xPos, yPos, type){

}
Enemy::~Enemy(){

}

void Enemy::RegisterHero( const Hero* hero )
{
	m_pCurrentLockedHero = hero;
}

void Enemy::SpecialEntityChecks( float dTime )
{
	if(m_pCurrentLockedHero->GetAlive())
	{
		//SpecialEnemyChecks(dTime, m_pCurrentLockedHero->GetPosition());
		m_pEnemyBehavior->Update(dTime, m_pCurrentLockedHero,this);
	}
	//uitbreiding multiplayer -> vraag aan entitymanager voor een nieuwe hero om te locken
}

void Enemy::SetBehavior( EnemyBehavior* behavior )
{
	m_pEnemyBehavior = behavior;
}