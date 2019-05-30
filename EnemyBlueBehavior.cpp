//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBlueBehavior
//							  Date: 20/8/2009
//******************************************************************************************

#include "stdafx.h"
#include "EnemyBlueBehavior.h"
#include "Hero.h"
#include "GameManager.h"
EnemyBlueBehavior::EnemyBlueBehavior(){
	m_fCurrentAttackTimer = 2.0f;
	m_fTotalAttackTimer = 2.0f;
}
EnemyBlueBehavior::~EnemyBlueBehavior(){

}

void EnemyBlueBehavior::Update(float dTime, const Hero* hero, Enemy* enemy)
{
	//check what to do depending on AI
	m_fCurrentAttackTimer += dTime;

	if(m_fCurrentAttackTimer > m_fTotalAttackTimer)
	{
		DoAction(hero->GetPosition(), enemy, dTime);
	}
}

void EnemyBlueBehavior::DoAction(const Vector2D& position, Enemy* enemy, float dTime)
{
	float randbreedte(50.0f);


	//zorg dat hij wat weg blijft van de rand
	if(enemy->GetPosition().x < randbreedte)
	{
		//we zitten bij de rand terug keren
		enemy->MoveRight(dTime);
		return;
	}

	if(enemy->GetPosition().x > GameManager::GetSingleton()->GetScreenWidth() - randbreedte)
	{
		enemy->MoveLeft(dTime);
		return;
	}

	//bepaal door random

	int randomgetal = rand() % 20 + 1;

	if(randomgetal < 5)
	{
		enemy->MoveLeft(dTime);
	}

	else if(randomgetal > 5 && randomgetal<10)
	{
		enemy->MoveRight(dTime);
	}

	else if(randomgetal >10 && randomgetal<13)
	{
		enemy->SetIdle();
	}

	else if(randomgetal >13 && randomgetal< 16)
	{
		enemy->Jump();
	}

	else if(randomgetal >16 && randomgetal<19)
	{
		enemy->Jump();
		enemy->MoveLeft(dTime);
	}

	else if(randomgetal >19 && randomgetal<21)
	{
		enemy->Jump();
		enemy->MoveRight(dTime);
	}

	//switch(randomgetal)
	//{
	//case (1 | 8 || 11 | 12 | 13 | 14):
	//	//loop naar positie links
	//	enemy->MoveLeft(dTime);
	//break;

	//case (2 | 9 | 15 | 16 | 17 | 18):
	//	//loop naar positie rechts
	//	enemy->MoveRight(dTime);
	//break;

	//case (3 | 10 | 7):
	//	//jump
	//	enemy->Jump();
	//break;

	//case 4:
	//	//jump links
	//	enemy->Jump();
	//	enemy->MoveLeft(dTime);
	//break;

	//case 5:
	//	//jump rechts
	//	enemy->Jump();
	//	enemy->MoveRight(dTime);
	//break;

	//case (6 | 19 | 20):
	//	//idle
	//	enemy->SetIdle();
	//break;

	//default:
	//	//shouldn't come here
	//	//assert
	//break;
	//}

	m_fCurrentAttackTimer = 0.0f;
	m_fTotalAttackTimer = (rand() % 100 + 1)/60.0f;

}