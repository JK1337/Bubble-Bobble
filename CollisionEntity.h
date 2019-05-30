//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionEntity
//							  Date: 28/7/2009
//******************************************************************************************

#ifndef CollisionEntity_H_INCLUDED
#define CollisionEntity_H_INCLUDED

#include "BaseEntity.h"
class CollisionData;
#include "LevelCollisionItemComponent.h"

class CollisionEntity : public BaseEntity {
public:
	CollisionEntity(int x, int y, int width, int height, const CollisionData* data);
	CollisionEntity(int x, int y, int width, int height);
	virtual ~CollisionEntity();
	virtual void InitCollisionItem(InitCollisionItemStruct mystruct, const string& pathtofile1, const string& pathtofile2, const string& pathtofile3);
	
	virtual bool Draw();
	virtual RECT GetRect();
private:
	const CollisionData* m_pCollisionData;
	vector<hgeSprite*> m_vSprites;
	float m_fMinimumPlaneWidth;
	bool m_bDraw;
	CollisionEntity(const CollisionEntity& t);
	CollisionEntity& operator=(const CollisionEntity& t);
	
};

#endif