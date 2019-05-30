//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameSettings
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "GameSettings.h"
#include "CharacterSetting.h"
#include "StringUtil.h"

GameSettings::GameSettings():m_sLastMade("Default")
{

}
GameSettings::~GameSettings()
{

}

void GameSettings::AddCharacter( CharacterSetting* setting )
{
	//we houden de laatst gemaakte bij
	//om te editen vanuit de xml parser
	m_sLastMade = setting->GetName();
	m_vCharacterSettings.insert(std::make_pair(setting->GetName(), setting));
}

CharacterSetting* GameSettings::EditLastCharacter()
{
	//return m_vCharacterSettings
	return (*m_vCharacterSettings.find(m_sLastMade)).second;
}

CharacterSetting* GameSettings::GetCharacterSettingByName(string name) const
{
	return (*m_vCharacterSettings.find(name)).second;
}

const std::map<string, CharacterSetting*>& GameSettings::GetCharacters() const
{
	return m_vCharacterSettings;
}

