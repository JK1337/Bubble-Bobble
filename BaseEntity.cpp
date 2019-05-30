//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: BaseEntity
//							  Date: 10/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "BaseEntity.h"
#include "GameManager.h"

BaseEntity::BaseEntity(double xPos, double yPos, double width, double height):m_vPosition(xPos,yPos), 
																m_dWidth(width), m_dHeight(height)
{

}

BaseEntity::BaseEntity( Vector2D position ,double width, double height):m_vPosition(position),m_dWidth(width), m_dHeight(height)
{

}
BaseEntity::~BaseEntity(){
	delete m_pSpr;
	GameManager::GetSingleton()->GetGameEngine()->Texture_Free(m_Tex);
}

void BaseEntity::Init(const string& texname)
{
	LoadTexture(texname); 
}

void BaseEntity::LoadTexture(const string& texname)
{
	//todo hou screensizes bij in manager class
	//todo hou path bij in manager class / relative shit
	string pathname = GameManager::GetSingleton()->GetArtPath();
	string pathtotexture = pathname + texname;
	m_Tex= GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());
	m_pSpr = new hgeSprite(m_Tex, 0, 0, m_dWidth, m_dHeight);
}

bool BaseEntity::Draw()
{
	m_pSpr->Render(m_vPosition.x,m_vPosition.y);
	return false;
}

bool BaseEntity::Tick(float dTime)
{
	//update texture? not needed..
	return false;
}

hgeSprite* BaseEntity::GetSprite()
{
	return m_pSpr;
}


//load texture met andere width & height
void BaseEntity::LoadTextureWH( const string& texname, float width, float height )
{
	//todo hou screensizes bij in manager class
	//todo hou path bij in manager class / relative shit
	string pathname = GameManager::GetSingleton()->GetArtPath();
	string pathtotexture = pathname + texname;
	m_Tex= GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());
	m_pSpr = new hgeSprite(m_Tex, 0, 0, width, height);
}