//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionMap
//							  Date: 28/7/2009
//******************************************************************************************

#ifndef COLLISIONMAP_H_INCLUDED
#define COLLISIONMAP_H_INCLUDED

#include <vector>
#include "Vector2D.h"
#include "hge.h"
class hgeSprite;
class MovingEntity;
class Level;


class CollisionMap {
public:
	virtual ~CollisionMap();
	static CollisionMap* GetSingleton();
	virtual void Init();
	void AddItem(const RECT& dimension, int id);
	Vector2D CheckCollision(RECT dimension,  const MovingEntity* entity);
	void SetCurrentLevel(const Level* level);
	void Draw();
private:
	CollisionMap();
	static CollisionMap* m_pCollisionMap;
	vector<char> m_vMapInfo;
	const Level* m_pLevel;
	hgeSprite* m_pSprGreen, *m_pSprRed;
	HTEXTURE m_TexGreen, m_TexRed;
	CollisionMap(const CollisionMap& t);
	CollisionMap& operator=(const CollisionMap& t);
	Vector2D HandleCollisionPoint(char id,  RECT dimension, const Vector2D& toplefthitpoint, const MovingEntity* entity);
	Vector2D FindIntersection(POINT p1,POINT p2, POINT p3,POINT p4);
	Vector2D FindIntersectionFast(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void LoadTextureIntoSprite(const string& textname, hgeSprite*& sprite,HTEXTURE& tofillin);

};

#endif