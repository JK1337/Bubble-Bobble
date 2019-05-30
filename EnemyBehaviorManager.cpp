//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyBehaviorManager
//							  Date: 24/8/2009
//******************************************************************************************

#include "stdafx.h"
#include "EnemyBehaviorManager.h"
#include "EnemyBlueBehavior.h"

EnemyBehaviorManager* EnemyBehaviorManager::m_pInstance = NULL;

EnemyBehaviorManager::EnemyBehaviorManager(){

}
EnemyBehaviorManager::~EnemyBehaviorManager(){

}

void EnemyBehaviorManager::Init()
{
	m_mapBehaviors.insert(std::make_pair(string("enemyblue"), new EnemyBlueBehavior()));
}

EnemyBehaviorManager* EnemyBehaviorManager::GetSingleton()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new EnemyBehaviorManager();
		m_pInstance->Init();
	}

	return m_pInstance;
}


EnemyBehavior* EnemyBehaviorManager::GetBehavior( const string& behaviorname )
{
	map<string, EnemyBehavior*>::iterator It = m_mapBehaviors.find(behaviorname);
	if(It != m_mapBehaviors.end())
	{
		return (*It).second;
	}else
	{
		//ASSERT
		return (*It).second;
	}
}