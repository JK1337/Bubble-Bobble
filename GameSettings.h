//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameSettings
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef GAMESETTINGS_H_INCLUDED
#define GAMESETTINGS_H_INCLUDED

#include <map>
using namespace std;
class CharacterSetting;

class GameSettings {
public:
	GameSettings();
	virtual ~GameSettings();

	void AddCharacter(CharacterSetting* setting);
	CharacterSetting* EditLastCharacter();
	const std::map < string, CharacterSetting*> & GetCharacters() const;
	CharacterSetting* GetCharacterSettingByName(string name) const;


private:
	std::map<string, CharacterSetting*>				m_vCharacterSettings;
	std::string										m_sLastMade;
	GameSettings(const GameSettings& t);
	GameSettings& operator=(const GameSettings& t);


};

#endif