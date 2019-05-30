//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameManager
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include "../include/hge.h"
#include "stdafx.h"
#include <map>

struct ToolComponentStruct
{
	string name;
	string filename;
	double width;
	double height;
};

class GameManager {
public:
	virtual ~GameManager();
	static GameManager* GetSingleton();
	void SetGameEngine(HGE* engine);
	HGE* GetGameEngine();
	const string& GetArtPath() const;
	const string& GetPath(std::string type) const;
	void AddPath(const std::pair<std::string,std::string>& mypair);
	void AddFileName(ToolComponentStruct mystruct);
	const ToolComponentStruct& GetFileName(const string& filename) const;
	void SetScreenWidth(float width);
	void SetScreenHeight(float height);
	float GetScreenWidth();
	float GetScreenHeight();
private: 
	GameManager();

	static GameManager*			m_pGameManager;
	HGE*						m_pEngine;
	string						m_sArtPath;
	float						m_fScreenWidth, m_fScreenHeight;
	typedef std::map<std::string, std::string> StringStringMap;
	StringStringMap m_mapPaths;
	typedef std::map<std::string, ToolComponentStruct> StringComponentMap;
	StringComponentMap m_mapFilenames;
	GameManager(const GameManager& t);
	GameManager& operator=(const GameManager& t);

};

#endif