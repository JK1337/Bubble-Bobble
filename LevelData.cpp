//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelData
//							  Date: 27/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "LevelData.h"
#include "ItemData.h"
#include "CollisionData.h"
LevelData::LevelData(){

}
LevelData::~LevelData(){

}

void LevelData::AddItemData( ItemData* data )
{
	m_vItemData.push_back(data);
}

void LevelData::AddCollisionData( CollisionData* data )
{
	m_vCollisionData.push_back(data);
}

void LevelData::AddEnemyData(ItemData* data)
{
	m_vEnemyData.push_back(data);
}

const vector<ItemData*>& LevelData::GetAllItemData() const
{
	return m_vItemData;
}

const vector<CollisionData*>& LevelData::GetAllCollisionData() const
{
	return m_vCollisionData;
}

const vector<ItemData*>& LevelData::GetAllEnemyData() const
{
	return m_vEnemyData;
}