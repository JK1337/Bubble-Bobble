//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Game
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class BaseEntity;
class GameSettings;
class MovingEntity;
class Hero;
class Level;
class IntroScreenGUI;
class GuiSettings;
class LevelEditor;
class LevelSettings;

class Game {
public:
	Game();
	virtual ~Game();

	bool Render();
	bool Update(float dTime);

private:
	Hero* m_pHero;
	Level* m_pLevel;
	Level* m_pOldLevel;
	IntroScreenGUI* m_pGUI;
	GameSettings* m_pGameSettings;
	GuiSettings* m_pGuiSettings;
	LevelEditor* m_pLevelEditor;
	LevelSettings* m_pLevelSettings;
	float m_fCurrentGameCounter, m_fTotalGameCounter;
	BaseEntity* m_pSprGameOver;
	Game(const Game& t);
	Game& operator=(const Game& t);
	void InitGame();

	void ReadXMLGameSettings();
	void ReadXMLGuiSettings();
	void ReadXMLLevelSettings();

	void CreatePlayers();

	bool HandleKeyEvents(float dt);

	void LoadLevel();
	void LoadGUI();
	void CreateLevelEditor();
	void CreateNewLevel();

};

#endif