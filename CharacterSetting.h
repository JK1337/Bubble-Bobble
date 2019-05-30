//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CharacterSettings
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef CHARACTERSETTINGS_H_INCLUDED
#define CHARACTERSETTINGS_H_INCLUDED

class AnimationSetting;
class SpriteSheetSetting;

#include <vector>
#include <map>
using namespace std;


class CharacterSetting {
public:

	CharacterSetting();
	virtual ~CharacterSetting();
	
	void SetName(const tstring& name);
	const string& GetName() const;
	
	void SetSpeed(float speed);
	float GetSpeed() const;

	void AddAnimation(AnimationSetting* animsetting);
	const AnimationSetting* GetAnimationByName(tstring name) const;

	void SetStartAnimation(const tstring& startanimation);
	const tstring& GetStartAnimation() const;

	void SetSpriteSheetSetting(SpriteSheetSetting* setting);
	const SpriteSheetSetting* GetSpriteSheetSetting() const;

private:

	string										m_sName;
	float										m_fSpeed;
	std::map <tstring , AnimationSetting*>	m_mapAnimationSettings;
	tstring										m_sStartAnimation;
	SpriteSheetSetting*							m_pSpriteSheetSetting;

	CharacterSetting(const CharacterSetting& t);
	CharacterSetting& operator=(const CharacterSetting& t);
	
};

#endif