//******************************************************************************************
//							Author: Allaert - McCann
//							 Class: StateManager
//							  Date: 14/4/2009
//******************************************************************************************

#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

enum GameState {
	GAMESTATEINVALID = 0,
	STOPPED = 1, 
	STARTED = 2, 
	PAUSED = 3, 
	LOADING = 4, 
	ENDGAME = 5,
	LEVELENDING = 6,
	GAMEOVER = 7,
	SWITCHLEVEL = 8
};

enum GameType {
	GAMETYPEINVALID = 0,
	SANDBOX = 1, 
	MULTIPLAYER = 2, 
	NONE = 3
};

enum NetworkType{
	NETWORKTYPEINVALID = 0,
	HOST = 1,
	CLIENT = 2
};

enum TypingState{
	TYPINGSTATEINVALID = 0,
	INTERFACE = 1,
	CONSOLE = 2,
	INGAME = 3
};

enum GuiState{
	GUISTARTSCREEN = 0,
	GUISAVEGAMESSCREEN = 1,
	GUIGAMESTARTED	= 2,
	GUIPAUSESCREEN = 3,
	GUISAVING = 4
};

class StateManager {
public:
	/** Returns StateManager pointer */
	static StateManager* GetSingleton();

	virtual ~StateManager();

	void Init();

	/** Set the Gamestate */
	void SetGameState(GameState state);

	/** Returns GameState */
	GameState GetGameState();

	/* GUI States*/
	void SetGuiState(GuiState state);
	GuiState GetGuiState();


	/** Set the GameType */
	void SetGameType(GameType type);

	/** Returns GameType */
	GameType GetGameType();

	/** Set the NetworkType */
	void SetNetworkType(NetworkType type);

	/** Returns NetworkType */
	NetworkType GetNetworkType();

	/** Set the TypingState */
	void SetTypingState(TypingState type);

	/** Returns TypingState */
	TypingState GetTypingState();




private:
	StateManager();
	
	GameState m_MyGameState;
	GameType m_MyGameType;
	NetworkType m_MyNetworkType;
	TypingState m_TypingState;
	GuiState m_MyGuiState;
	static StateManager* m_StateManagerPtr;
	StateManager(const StateManager& t);
	StateManager& operator=(const StateManager& t);
};

#endif