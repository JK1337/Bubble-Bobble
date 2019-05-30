//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EntityManager
//							  Date: 14/7/2009
//******************************************************************************************

#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

class GameSettings;
class MovingEntity;
class Hero;
class ItemData;
class Enemy;

#include <vector>
#include <algorithm>

class EntityManager {
public:

	virtual ~EntityManager();
	static EntityManager* GetSingleton();
	
	void SetSettingsPointer(const GameSettings* settings);
	void CreateBubble(float xPos, float yPos, bool dir);
	void CreateEnemy(const ItemData* data);
	bool Tick(float dTime);
	void ToggleCollisionDebug();
	bool Render();
	void RegisterDeadEntity(MovingEntity* entity);
	bool HeroBubbleCollision(const Hero* hero);
	bool HeroEnemyCollision(const Hero* hero);
	void SetCurrentHero(const Hero* hero);
	void DropPresent(const Vector2D& launchposition);
	void DecreaseEntities();
	void IncreaseEntities();
private:
	const GameSettings* m_pGameSettings;
	const Hero* m_pCurrentHero;
	static EntityManager*			m_pEntityManager;
	EntityManager();
	EntityManager(const EntityManager& t);
	EntityManager& operator=(const EntityManager& t);
	void CheckForDeleteDeadOnes();
	Enemy* GetEnemyByName(const std::string& name);
	void EnemyBubbleCollisionCheck();
	void DeleteMovingEntities();
	bool m_bClearAll;
	unsigned int m_iDeleteItemCounter;
	int m_iNumEntities;
	std::vector<MovingEntity*> m_vMovingEntities;
	std::vector<BaseEntity*> m_vBaseEntities;
	std::vector<MovingEntity*> m_vItemsToDelete;

};

#endif