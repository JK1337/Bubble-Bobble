//******************************************************************************************
//							Author: Allaert - McCann
//							 Class: GameStateManager
//							  Date: 14/4/2009
//******************************************************************************************

#include "stdafx.h"
#include "StateManager.h"

StateManager* StateManager::m_StateManagerPtr = NULL;

StateManager::StateManager(){

}
StateManager::~StateManager(){

}

StateManager* StateManager::GetSingleton(){
	if(m_StateManagerPtr == NULL)
		m_StateManagerPtr = new StateManager();
	return m_StateManagerPtr;
}

void StateManager::SetGameState( GameState state ){
	m_MyGameState = state;
}

GameState StateManager::GetGameState(){
	return m_MyGameState;
}

void StateManager::SetGameType( GameType type ){
	m_MyGameType = type;
}

GameType StateManager::GetGameType(){
	return m_MyGameType;
}

void StateManager::SetNetworkType( NetworkType type )
{
	m_MyNetworkType = type;
}

NetworkType StateManager::GetNetworkType()
{
	return m_MyNetworkType;
}

void StateManager::SetTypingState( TypingState type )
{
	m_TypingState = type;
}

TypingState StateManager::GetTypingState()
{
	return m_TypingState;
}

void StateManager::Init()
{
	 m_MyGameState = GAMESTATEINVALID;
	 m_MyGameType = GAMETYPEINVALID;
	 m_MyNetworkType = NETWORKTYPEINVALID;
	 m_TypingState = TYPINGSTATEINVALID;
}

void StateManager::SetGuiState( GuiState state )
{
	m_MyGuiState = state;
}

GuiState StateManager::GetGuiState()
{
	return m_MyGuiState;
}