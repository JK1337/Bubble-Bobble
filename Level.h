//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Level
//							  Date: 14/7/2009
//******************************************************************************************

#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

class hgeSprite;
class CollisionEntity;
#include "BaseEntity.h"
#include "hge.h"
class LevelData;

class Level {
public:
	Level(const LevelData* leveldata);
	virtual ~Level();
	virtual void Init();
	//virtual void Update(float dTime);
	virtual void Draw();
	virtual const vector<CollisionEntity*>& GetCollisionItems()  const;
	void ToggleCollisionDebug();
protected:
	const LevelData* m_pLevelData;
	vector<BaseEntity*> m_vBackgroundItems;
	vector<CollisionEntity*> m_vCollisionItems;
	hgeQuad m_quad;
	void InitQuad();
	
private:
	bool m_bCollisionCheck;
	Level(const Level& t);
	Level& operator=(const Level& t);
	void CreateGroundCollision();
};

#endif