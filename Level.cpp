//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Level
//							  Date: 14/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "Level.h"

#include "..\include\hge.h"
#include "..\include\hgesprite.h"

#include "hge.h"

#include "GameManager.h"

#include "LevelData.h"
#include <algorithm>
#include "ItemData.h"
#include "LevelCollisionItemComponent.h"
#include "CollisionData.h"
#include "CollisionEntity.h"
#include "MyGameDefines.h"
#include "CollisionMap.h"
#include "EntityManager.h"



Level::Level(const LevelData* leveldata):m_pLevelData(leveldata),m_bCollisionCheck(false)
{
	CollisionMap::GetSingleton()->SetCurrentLevel(this);
}

Level::~Level(){
	GAME_ENGINE->Texture_Free(m_quad.tex);
}

class FCreateBackGroundItem
{
public:
	FCreateBackGroundItem(std::vector<BaseEntity*>& vToFillIn):m_vBackGroundItems(vToFillIn),
		m_sExtraPath("LevelObjects/full/"){};
	void operator()(const ItemData* itemdata)
	{
		BaseEntity* entity = new BaseEntity(itemdata->GetX(), itemdata->GetY(), itemdata->GetWidth(), itemdata->GetHeight());
		entity->Init(m_sExtraPath + itemdata->GetName() + ".png");
		m_vBackGroundItems.push_back(entity);
	}
private:
	std::vector<BaseEntity*>& m_vBackGroundItems;
	std::string m_sExtraPath;
};

class FCreateCollisionItem
{
public:
	FCreateCollisionItem(std::vector<CollisionEntity*>& vToFillIn):m_vCollisionItems(vToFillIn), m_sLevelObjPath(GameManager::GetSingleton()->GetPath("levelobj")),m_iCounter(0){};
	void operator()(const CollisionData* collisiondata)
	{
		CollisionEntity* entity = new CollisionEntity(collisiondata->GetX(), collisiondata->GetY(), collisiondata->GetWidth(), collisiondata->GetHeight(), collisiondata);


		InitCollisionItemStruct collisionStruct;

		//path opmaken, kan voor verschillende collision items nog gebruikt worden
		string objectname = collisiondata->GetName();
		string objectone = objectname + "start";
		ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName(objectone);
		collisionStruct.width1 = myStruct.width;
		collisionStruct.height1 = myStruct.height;
		string pathtofile1 = m_sLevelObjPath + "full/" + myStruct.filename;

		//sprite 2 path maken
		string objecttwo = objectname + "mid";
		myStruct = GameManager::GetSingleton()->GetFileName(objecttwo);
		collisionStruct.width2 = myStruct.width;
		collisionStruct.height2 = myStruct.height;
		string pathtofile2 = m_sLevelObjPath + "full/" + myStruct.filename;

		//sprite 3 path maken
		string objectthree = objectname + "end";
		myStruct = GameManager::GetSingleton()->GetFileName(objectthree);
		collisionStruct.width3 = myStruct.width;
		collisionStruct.height3 = myStruct.height;
		string pathtofile3 = m_sLevelObjPath + "full/" + myStruct.filename;
		
		entity->InitCollisionItem(collisionStruct, pathtofile1, pathtofile2, pathtofile3);

		//voeg toe aan de collisionmap
		CollisionMap::GetSingleton()->AddItem(entity->GetRect(), m_iCounter);

		m_vCollisionItems.push_back(entity);

		++m_iCounter;
	}
private:
	string m_sLevelObjPath;
	vector<CollisionEntity*>& m_vCollisionItems;
	int m_iCounter;
};


class FCreateEnemyItem
{
public:
	FCreateEnemyItem(){};
	void operator()(const ItemData* data)
	{
		//we maken een enemy aan met de data
		EntityManager::GetSingleton()->CreateEnemy(data);
	}
};

void Level::Init()
{
	//laad background in voor 't level
	InitQuad();

	//we laden alle items in van het level
	for_each(m_pLevelData->GetAllItemData().begin()	, m_pLevelData->GetAllItemData().end(), FCreateBackGroundItem(m_vBackgroundItems));
	//we laden alle collision items in van het level
	//sprite 1 path maken 
	for_each(m_pLevelData->GetAllCollisionData().begin(), m_pLevelData->GetAllCollisionData().end(), FCreateCollisionItem(m_vCollisionItems));
	for_each(m_pLevelData->GetAllEnemyData().begin(), m_pLevelData->GetAllEnemyData().end(), FCreateEnemyItem());

	CreateGroundCollision();
}


void Level::CreateGroundCollision()
{
	float m_fGroundHeight(136.0f);
	RECT dimension;
	dimension.left = 0;
	dimension.right = GameManager::GetSingleton()->GetScreenWidth();
	dimension.bottom = GameManager::GetSingleton()->GetScreenHeight();
	dimension.top = dimension.bottom - m_fGroundHeight;
	CollisionEntity* entity = new CollisionEntity(dimension.left, dimension.top, dimension.right - dimension.left,dimension.bottom - dimension.top );
	m_vCollisionItems.push_back(entity);
	//als id nemen we de size van de vector -1 omdat hij 't laatst toegevoegd item is
	CollisionMap::GetSingleton()->AddItem(dimension, m_vCollisionItems.size()-1);
}

/*
void Level::Update( float dTime )
{
	
}
*/ 

class FRenderBackGroundItem
{
public:
	FRenderBackGroundItem(){};
	void operator()(BaseEntity* entity)
	{
		entity->Draw();
	}
};
// 
 class FRenderCollisionLines
 {
 public:
 	FRenderCollisionLines(){};
 	void operator()(CollisionEntity* entity)
 	{
		GAME_ENGINE->Gfx_RenderLine(	entity->GetRect().left, 	entity->GetRect().top, 	entity->GetRect().right, 	entity->GetRect().top,
			0xFFFFFFFF, 0.1);
		GAME_ENGINE->Gfx_RenderLine( entity->GetRect().left, 	entity->GetRect().bottom, 	entity->GetRect().right, 	entity->GetRect().bottom, 0xFFFFFFFF, 0.1);
		GAME_ENGINE->Gfx_RenderLine( entity->GetRect().left, 	entity->GetRect().top, 	entity->GetRect().left, 	entity->GetRect().bottom, 0xFFFFFFFF, 0.1);
		GAME_ENGINE->Gfx_RenderLine( entity->GetRect().right, 	entity->GetRect().top, 	entity->GetRect().right, 	entity->GetRect().bottom, 0xFFFFFFFF, 0.1);
 	}
 };
 

void Level::Draw()
{
	GAME_ENGINE->Gfx_RenderQuad(&m_quad);
	for_each(m_vBackgroundItems.begin()	, m_vBackgroundItems.end(), FRenderBackGroundItem());
	for_each(m_vCollisionItems.begin(), m_vCollisionItems.end(), FRenderBackGroundItem());

	if(m_bCollisionCheck)
		for_each(m_vCollisionItems.begin(), m_vCollisionItems.end(), FRenderCollisionLines());
	
}

void Level::InitQuad()
{
	float screenWidth(GameManager::GetSingleton()->GetScreenWidth());
	float screenHeight(GameManager::GetSingleton()->GetScreenHeight());
	m_quad.v[0].x=0; m_quad.v[0].y=0;
	m_quad.v[1].x=screenWidth; m_quad.v[1].y=0;
	m_quad.v[2].x=screenWidth; m_quad.v[2].y=screenHeight;
	m_quad.v[3].x=0; m_quad.v[3].y=screenHeight;
	m_quad.blend = BLEND_NOZWRITE;
	m_quad.v[0].tx=0; m_quad.v[0].ty=0; 
	m_quad.v[1].tx=1; m_quad.v[1].ty=0; 
	m_quad.v[2].tx=1; m_quad.v[2].ty=1; 
	m_quad.v[3].tx=0; m_quad.v[3].ty=1; 

	for(int i=0;i<4;i++)
	{
		m_quad.v[i].z=0.9f;
		m_quad.v[i].col=0xFFFFFFFF;
	}

	string sbackground = GameManager::GetSingleton()->GetArtPath() + "Levels/Achtergrond.png";
	m_quad.tex = GAME_ENGINE->Texture_Load(sbackground.c_str());
}

const vector<CollisionEntity*>& Level::GetCollisionItems() const
{
	return m_vCollisionItems;
}	

void Level::ToggleCollisionDebug()
{
	m_bCollisionCheck = !m_bCollisionCheck;
}