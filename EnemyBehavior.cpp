//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBehavior
//							  Date: 20/8/2009
//******************************************************************************************
#include "stdafx.h"
#include "EnemyBehavior.h"
#include "Hero.h"
#include "Enemy.h"
EnemyBehavior::EnemyBehavior(){
	
}

EnemyBehavior::~EnemyBehavior(){
	
}

void EnemyBehavior::Update( float dTime, const Hero* hero, Enemy* enemy )
{
	m_fCurrentAttackTimer += dTime;
}