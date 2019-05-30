//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Game
//							  Date: 10/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "BaseEntity.h"
#include "MovingEntity.h"
#include "Game.h"
#include "GameSettings.h"
#include "XMLParser.h"
#include "GameManager.h"
#include "Hero.h"
#include "Level.h"
#include "EntityManager.h"
#include "IntroScreenGUI.h"
#include "MyGameDefines.h"
#include "GuiSettings.h"
#include "LevelEditor.h"
#include "LevelEditorGUI.h"
#include "LevelSettings.h"
#include "StateManager.h"
#include "CollisionMap.h"
#define CURRENTGAMESTATE StateManager::GetSingleton()->GetGameState()
Game::Game():m_pGUI(0), m_pHero(0), m_pLevel(0),m_pLevelEditor(0), m_fCurrentGameCounter(0), m_fTotalGameCounter(4),m_pSprGameOver(0)
{
	InitGame();
}
Game::~Game()
{
	delete m_pGameSettings;
	delete m_pHero;
	delete m_pGUI;
	delete m_pLevel;
	delete m_pLevelEditor;
	delete m_pSprGameOver;
}


void Game::InitGame()
{

	ReadXMLGameSettings();
	ReadXMLGuiSettings();
	ReadXMLLevelSettings();
	//CreateLevelEditor();
	EntityManager::GetSingleton()->SetSettingsPointer(m_pGameSettings);
	CreatePlayers();

	//CreateLevelEditor();
	LoadLevel();
	
	LoadGUI();
	
	///BaseEntity* m_pHero = new BaseEntity();
	//m_pHero->Init("hero.png", )
}

void Game::CreateLevelEditor()
{
	m_pLevelEditor = new LevelEditor(m_pGuiSettings);
	m_pLevelEditor->Init();
}

void Game::LoadGUI()
{
	m_pGUI = new IntroScreenGUI();
	m_pGUI->Init();
}

void Game::LoadLevel()
{
	m_pLevel = new Level(m_pLevelSettings->GetLevelData(0));
	//m_pLevel = new Level(m_pLevelSettings->GetLastMAde());
	m_pLevel->Init();
	StateManager::GetSingleton()->SetGameState(STARTED);
}

void Game::CreatePlayers()
{
	//m_pGameSettings->GetCharacters().begin(), 
	m_pHero = new Hero(m_pGameSettings->GetCharacterSettingByName("Hero"), 150, 150, HERO);
	EntityManager::GetSingleton()->SetCurrentHero(m_pHero);
	m_pHero->Init();
}

bool Game::Render()
{

	if(CURRENTGAMESTATE == ENDGAME)
	{
		if(m_pSprGameOver != 0)
			m_pSprGameOver->Draw();
	}else
	{
		if(m_pLevel != 0)
			m_pLevel->Draw();
		if(m_pLevelEditor != 0)
			m_pLevelEditor->Render();


		m_pGUI->Render();

		m_pHero->Draw();
		EntityManager::GetSingleton()->Render();
	}


	return false;
}

bool Game::Update(float dTime)
{

	HandleKeyEvents(dTime);
	
	m_pGUI->Update(dTime);
	
	if(m_pLevelEditor != 0)
		m_pLevelEditor->Update(dTime);
	
	if(CURRENTGAMESTATE != GAMEOVER && CURRENTGAMESTATE != ENDGAME)
		m_pHero->Tick(dTime);

	if(CURRENTGAMESTATE == STARTED || CURRENTGAMESTATE == LEVELENDING)
		EntityManager::GetSingleton()->Tick(dTime);

	if(CURRENTGAMESTATE == LEVELENDING)
	{
		//hou teller bij om de player nog snel de presents te laten halen
		m_fCurrentGameCounter += dTime;
			if(m_fCurrentGameCounter > m_fTotalGameCounter)
			{
				Vector2D spawnposition(100,100);
				m_pHero->PrepareForNewLevel(spawnposition);
				CreateNewLevel();
				StateManager::GetSingleton()->SetGameState(SWITCHLEVEL);
				m_fCurrentGameCounter = 0;
			}
	}


	if(CURRENTGAMESTATE == GAMEOVER)
	{
		delete m_pHero;
		delete m_pLevel;
		delete EntityManager::GetSingleton();
		//**/delete CollisionMap::GetSingleton();
		float height = 53.0f;
		float width = 250.0f;
		m_pSprGameOver = new BaseEntity(Vector2D(GameManager::GetSingleton()->GetScreenWidth()/2.0f-width/2.0f,GameManager::GetSingleton()->GetScreenHeight()/2.0f-height/2.0f), width, height);
		m_pSprGameOver->Init("Algemeen/GameOver.png");

		StateManager::GetSingleton()->SetGameState(ENDGAME);
	}
	return false;
}

void Game::CreateNewLevel()
{
	m_pOldLevel = m_pLevel;
	m_pLevel = new Level(m_pLevelSettings->GetLevelData(0));
	m_pLevel->Init();	
}

void Game::ReadXMLGameSettings()
{

	//eerste de main game settings inlezen
	tifstream file(_T("xml/bubble_bobble.xml"));

	if (!file)
		return;
	tstring line, XML_Code;
	while (!file.eof())
	{
		getline(file,line);
		XML_Code += line;
	}
	file.close();
	
	m_pGameSettings = new GameSettings();
	XMLParser parser(m_pGameSettings);
	parser.skipWhiteSpace(XML_Code); //speciale tekens eruit gooien
	parser.XML_Parse(XML_Code, true);
}

void Game::ReadXMLGuiSettings()
{
	//eerste de main game settings inlezen
	tifstream file(_T("xml/bubble_bobble_gui.xml"));

	if (!file)
		return;
	tstring line, XML_Code;
	while (!file.eof())
	{
		getline(file,line);
		XML_Code += line;
	}
	file.close();

	m_pGuiSettings = new GuiSettings();
	XMLParserGUI parser(m_pGuiSettings);
	parser.skipWhiteSpace(XML_Code); //speciale tekens eruit gooien
	parser.XML_Parse(XML_Code, true);
}

void Game::ReadXMLLevelSettings()
{
	//eerste de main game settings inlezen
	tifstream file(_T("xml/levels.xml"));

	if (!file)
		return;
	tstring line, XML_Code;
	while (!file.eof())
	{
		getline(file,line);
		XML_Code += line;
	}
	file.close();

	m_pLevelSettings = new LevelSettings();
	XMLParserLevel parser(m_pLevelSettings);
	parser.skipWhiteSpace(XML_Code); //speciale tekens eruit gooien
	parser.XML_Parse(XML_Code, true);
}




bool Game::HandleKeyEvents(float dt)
{
	bool bIdle(true);

	if (GAME_ENGINE->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if(CURRENTGAMESTATE == STARTED || CURRENTGAMESTATE == LEVELENDING)
	{
		if(!m_pHero->GetDying() && m_pHero->GetAlive())
		{
			OutputDebugStringW(_T("-input-"));

			if (GAME_ENGINE->Input_GetKeyState(HGEK_LEFT))
			{
				m_pHero->MoveLeft(dt);
				bIdle = false;
			}


			if (GAME_ENGINE->Input_GetKeyState(HGEK_RIGHT)) 
			{
				m_pHero->MoveRight(dt);
				bIdle = false;
			}


			if (GAME_ENGINE->Input_GetKeyState(HGEK_ALT)) 
			{
				m_pHero->Attack();
				bIdle = false;
			}

			if (GAME_ENGINE->Input_GetKeyState(HGEK_SPACE))
			{
				//todo tenzij een zeepbel
				if(!m_pHero->GetJumping())
				{
					m_pHero->Jump();
					bIdle = false;
				}
			}

			if (!m_pHero->GetIdle() && bIdle && !(m_pHero->GetJumping()) && m_pHero->GetIdleReset())
				m_pHero->SetIdle();
		}
	}
	
	

	/*
	if( GAME_ENGINE->Input_GetKeyState(HGEK_DOWN))
	{
		m_pHero->StopJumping();
	}
	*/ 
	if( GAME_ENGINE->Input_GetKeyState(HGEK_F9))
	{
		m_pLevel->ToggleCollisionDebug();
		m_pHero->ToggleCollisionDebug();
		EntityManager::GetSingleton()->ToggleCollisionDebug();
	}


	
	

	//if (GAME_ENGINE->Input_GetKeyState(HGEK_UP)) dy-=speed*dt;
	//if (GAME_ENGINE->Input_GetKeyState(HGEK_DOWN)) dy+=speed*dt;.
	return false;
}

