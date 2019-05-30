//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelData
//							  Date: 27/7/2009
//******************************************************************************************

#ifndef LEVELDATA_H_INCLUDED
#define LEVELDATA_H_INCLUDED

class ItemData;
class CollisionData;

#include <vector>



class LevelData {
public:
	LevelData();
	virtual ~LevelData();
	virtual void AddItemData(ItemData* data);
	virtual void AddCollisionData(CollisionData* data);
	virtual void AddEnemyData(ItemData* data);
	const vector<ItemData*>& GetAllItemData() const;
	const vector<CollisionData*>& GetAllCollisionData() const;
	const vector<ItemData*>& GetAllEnemyData() const;

private:
	vector<ItemData*> m_vItemData;
	vector<CollisionData*> m_vCollisionData;
	vector<ItemData*> m_vEnemyData;
	LevelData(const LevelData& t);
	LevelData& operator=(const LevelData& t);
	
};

#endif