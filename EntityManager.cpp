//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EntityManager
//							  Date: 14/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "Bubble.h"
#include "EntityManager.h"
#include "MovingEntity.h"
#include "GameSettings.h"
#include "CollisionHelperClass.h"
#include "Hero.h"
#include "ItemData.h"
#include "EnemyBehaviorManager.h"
#include "StateManager.h"
#include "CollisionMap.h"
//enemies
#include "Enemy.h"



EntityManager* EntityManager::m_pEntityManager = NULL;


EntityManager::EntityManager():m_iDeleteItemCounter(0),m_iNumEntities(0), m_bClearAll(false){

}
EntityManager::~EntityManager(){
	delete CollisionMap::GetSingleton();
}

EntityManager* EntityManager::GetSingleton()
{
	if(m_pEntityManager == NULL)
	{
		m_pEntityManager = new EntityManager();
		
	}
	return m_pEntityManager;
}




void EntityManager::CreateBubble(float xPos, float yPos, bool dir)
{
	Bubble* newbubble = new Bubble(m_pGameSettings->GetCharacterSettingByName("Bubble"), xPos, yPos, dir, BUBBLE);
	newbubble->Init();
	m_vMovingEntities.push_back(newbubble);
}

void EntityManager::SetSettingsPointer(const GameSettings* settings)
{
	m_pGameSettings = settings;
}

class FTickMovable
{
public:
	FTickMovable(float dTime):m_dTime(dTime){};
	void operator()(MovingEntity* entity)
	{
		entity->Tick(m_dTime);
	}
private:
	float m_dTime;
};

class FRenderMovable
{
public:
	FRenderMovable(){}
	void operator()(MovingEntity* entity)
	{
		entity->Draw();
	}
};

bool EntityManager::Tick(float dTime)
{
	if(m_bClearAll)
		DeleteMovingEntities();
	std::for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FTickMovable(dTime));
	EnemyBubbleCollisionCheck();
	CheckForDeleteDeadOnes();
	return false;
}

bool EntityManager::Render()
{
	std::for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FRenderMovable());
	return false;
}

template<typename T>
void DeleteThatShit(T element)
{
	delete element;
	element = NULL;
}

class FDeleteMe
{
public:
	FDeleteMe(std::vector<MovingEntity*>& vDeleteFrom):m_vDeleteFrom(vDeleteFrom){};
	void operator()(MovingEntity* entity)
	{
		//we removen enkel van vector, we laten geen memory leaks omdat we de andere vector clearen (erase)
		/*remove(m_vDeleteFrom.begin(), m_vDeleteFrom.end(), entity);*/
		std::vector<MovingEntity*>::iterator It;
		for ( It = m_vDeleteFrom.begin(); It != m_vDeleteFrom.end(); )
		{
			if( (*It) == entity )
			{
				bool bDecrease(false);
				if((*It)->GetType() == ENEMY)
				{
					bDecrease = true;
				}else if ((*It)->GetType() == BUBBLE)
				{
					Bubble* bubble = dynamic_cast<Bubble*> ((*It));
					if(bubble->GetCaptured())
					{
						bDecrease = true;
					}
				}
				delete (*It);  
				It = m_vDeleteFrom.erase(It);
				if(bDecrease)
					EntityManager::GetSingleton()->DecreaseEntities();
			} else {
			 ++It;
			}
		}
	}

private:
	std::vector<MovingEntity*>& m_vDeleteFrom;
};

void EntityManager::CheckForDeleteDeadOnes()
{
	//we erasen eerst de items van de vector waar ze toe behoren
	if(m_vItemsToDelete.size() > 0)
	{
		if(m_vMovingEntities.size() > 0)
			for_each(m_vItemsToDelete.begin(), m_vItemsToDelete.end(), FDeleteMe(m_vMovingEntities));	
		m_vItemsToDelete.clear();
	}
}

class FToggleCollisionDebug
{
public:
	FToggleCollisionDebug(){};
	void operator()(MovingEntity* entity)
	{
		entity->ToggleCollisionDebug();
	}
};

void EntityManager::RegisterDeadEntity(MovingEntity* entity)
{
	m_vItemsToDelete.push_back(entity);
}

void EntityManager::ToggleCollisionDebug()
{
	std::for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FToggleCollisionDebug());
}

class FCheckBubbleCollision
{
public:
	FCheckBubbleCollision(const Hero* hero):m_pHero(hero), m_bJump(false){};
	void operator()(MovingEntity* entity)
	{
		bool bHit = CollisionHelperClass::CheckRectangleCollisions(entity->GetRect(), m_pHero->GetRect());
		if(bHit)
		{
			//check of we boven of onder het middelpunt zitten van de bubble om te deleten of niet
			if(entity->GetType() == BUBBLE)
			{
				if(!(entity->GetDying()))
				{
					Bubble* mybubble = dynamic_cast<Bubble*>(entity);

					// een hero heeft enkel interactie met een bubble als hij voorbij de 
					//beginfase is, dus na de fase waar hij enemies moet handlen
					if(!mybubble->HandleEnemies())
					{
						//we jumpen
           						if(  m_pHero->GetCurrentSpeed().y <= 0)
						{
							//we zitten onder de bubble
							//dood hem !
							entity->Kill();
						}else{
							if(mybubble->HandleJump())
							{
								//we zitten boven de bubble
								//jump!
								m_bJump = true;
							}
						}
					}
					
				}
				
			}
		}

	}

	bool m_bJump; 

private:
	const Hero* m_pHero;
};

bool EntityManager::HeroBubbleCollision(const Hero* hero)
{
	if(for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FCheckBubbleCollision(hero)).m_bJump)
	{
		return true;
	}else
	{
		return false;
	}
}	


class FCheckEnemyCollision
{
public:
	FCheckEnemyCollision(const Hero* hero):m_pHero(hero), m_bHit(false){};
	void operator()(MovingEntity* entity)
	{
		//check of we boven of onder het middelpunt zitten van de bubble om te deleten of niet
		if(entity->GetType() == ENEMY)
		{
			if(!(entity->GetDying()))
			{
				bool bHit = CollisionHelperClass::CheckRectangleCollisions(entity->GetRect(), m_pHero->GetRect());
				if(bHit)
				{
					m_bHit = true;
				}
			}
		}

	}

	bool m_bHit; 

private:
	const Hero* m_pHero;
};


bool EntityManager::HeroEnemyCollision(const Hero* hero)
{

	if(for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FCheckEnemyCollision(hero)).m_bHit)
	{
		return true;
	}else
	{
		return false;
	}
}

class FCheckHitCollision
{
public:
	FCheckHitCollision(vector<MovingEntity*>& entities, vector<MovingEntity*>& todelete):m_vMovingEntities(entities), m_vItemsToDelete(todelete){};
	void operator()(MovingEntity* entity)
	{
		if(entity->GetAlive() && !entity->GetDying())
		{
			if(entity->GetType() == ENEMY)
			{
				//test deze entiteit met onze bubbles in subfunctor
				if(for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FCheckWithBubble(entity)).m_bHit)
				{
					//std::vector<MovingEntity*>::iterator Pos = remove(m_vMovingEntities.begin(), m_vMovingEntities.end(), entity);
					//m_vMovingEntities.erase(remove(m_vMovingEntities.begin(), m_vMovingEntities.end(), entity), m_vMovingEntities.end());
					m_vItemsToDelete.push_back(entity);
					//m_vMovingEntities.erase(Pos, m_vMovingEntities.end());
				}
			}
		}
	}

private:
	vector<MovingEntity*>& m_vMovingEntities;
	vector<MovingEntity*>& m_vItemsToDelete;

	class FCheckWithBubble
	{
	public:
		FCheckWithBubble(MovingEntity* enemyToCheck):m_pEnemyToCheck(enemyToCheck),m_bHit(false){};
		void operator()(MovingEntity* entity)
		{
			if(entity->GetAlive() && (!entity->GetDying()))
			{
				if(entity->GetType() == BUBBLE)
				{
					Bubble* bubble = dynamic_cast<Bubble*>(entity);
					if(bubble->HandleEnemies())
					{
						bool bHit = CollisionHelperClass::CheckRectangleCollisions(entity->GetRect(), m_pEnemyToCheck->GetRect());
						if(bHit)
						{
							m_bHit = true;

							bubble->CaptureMode();
							EntityManager::GetSingleton()->IncreaseEntities();
						}				
					}
				}
			};
		}
	bool m_bHit;
	private:
		MovingEntity* m_pEnemyToCheck;
	};
};

void EntityManager::IncreaseEntities()
{
	++m_iNumEntities;
}

void EntityManager::EnemyBubbleCollisionCheck()
{
	for_each(m_vMovingEntities.begin(), m_vMovingEntities.end(), FCheckHitCollision(m_vMovingEntities, m_vItemsToDelete));
}

void EntityManager::CreateEnemy(const ItemData* data)
{
	CharacterSetting* enemysetting = m_pGameSettings->GetCharacterSettingByName(data->GetName());

	Enemy* enemy = new Enemy(enemysetting, data->GetX(), data->GetY(), ENEMY);
	enemy->SetBehavior(EnemyBehaviorManager::GetSingleton()->GetBehavior(data->GetName()));
	m_vMovingEntities.push_back(enemy);
	enemy->RegisterHero(m_pCurrentHero);
	enemy->Init();
	++m_iNumEntities;
}

void EntityManager::SetCurrentHero(const Hero* hero)
{
	m_pCurrentHero = hero;
}

void EntityManager::DropPresent( const Vector2D& launchposition )
{
	
}

void EntityManager::DecreaseEntities()
{
	--m_iNumEntities;
	if(m_iNumEntities == 0)
	{
		//NEXTLEVEL
		//state manager!
		StateManager::GetSingleton()->SetGameState(LEVELENDING);
		m_bClearAll = true;
		//remove all movable objects
		//m_vMovingEntities.clear();
	}
}

void EntityManager::DeleteMovingEntities()
{
	m_bClearAll = false;
	//copy all to delete vector
	m_vItemsToDelete.clear();
	m_vItemsToDelete.resize(m_vMovingEntities.size());
	copy(m_vMovingEntities.begin(), m_vMovingEntities.end(), m_vItemsToDelete.begin());
}
//class FSegmentToBufferOffset
//{
//public:
//	FSegmentToBufferOffset(Segment*& s, int VBIndex, DAEFloat2& offset): m_MySegment(s), m_CurrentIndex(VBIndex), m_Offset(offset)
//	{}
//
//	void operator()(const boost::shared_ptr< Segment > & segment)
//	{
//		//maak copy
//		Segment newsegment = *segment;
//		//vul offset in
//		newsegment.vPosition.x += m_Offset.x;
//		newsegment.vPosition.y += m_Offset.y;
//		m_MySegment[m_CurrentIndex] = newsegment;
//		++m_CurrentIndex;
//	}
//	int m_CurrentIndex;
//private:
//	Segment* m_MySegment;
//	DAEFloat2 m_Offset;
//};