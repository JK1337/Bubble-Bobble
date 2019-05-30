//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameManager
//							  Date: 10/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "GameManager.h"

GameManager* GameManager::m_pGameManager = NULL;

GameManager::GameManager():m_pEngine(NULL), m_sArtPath("../Bubble Bobble/Art/"){

}
GameManager::~GameManager(){

}

GameManager* GameManager::GetSingleton()
{
	if (m_pGameManager == NULL)
		m_pGameManager = new GameManager();
	return m_pGameManager;
}

void GameManager::SetGameEngine( HGE* engine )
{
	m_pEngine = engine;
}

HGE* GameManager::GetGameEngine()
{
	return m_pEngine;
}

const string& GameManager::GetArtPath() const
{
	return m_sArtPath;
}

const string& GameManager::GetPath(std::string type) const
{
	StringStringMap::const_iterator pathIt = m_mapPaths.find(type);
	if(pathIt != m_mapPaths.end())
		return (*pathIt).second;
	else //shouldnt be here...
		return "";
}

void GameManager::AddPath( const std::pair<std::string,std::string>& mypair )
{
	m_mapPaths.insert(mypair);
}

void GameManager::AddFileName( ToolComponentStruct mystruct )
{
	m_mapFilenames.insert(std::make_pair(mystruct.name, mystruct));
}

const ToolComponentStruct& GameManager::GetFileName(const string& name) const
{
	StringComponentMap::const_iterator myIt;
	myIt = m_mapFilenames.find(name);
	if(myIt != m_mapFilenames.end())
	{
		return (*myIt).second;
	}else
	{
		//todo
		//insert assert
		//shouldn't come here :)
		return ((*m_mapFilenames.begin()).second);
	}
}

void GameManager::SetScreenWidth( float width )
{
	m_fScreenWidth = width;
}

void GameManager::SetScreenHeight( float height )
{
	m_fScreenHeight = height;
}

float GameManager::GetScreenWidth()
{
	return m_fScreenWidth;
}

float GameManager::GetScreenHeight()
{
	return m_fScreenHeight;
}