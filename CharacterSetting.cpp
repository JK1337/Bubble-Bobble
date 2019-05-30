//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CharacterSettings
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "CharacterSetting.h"
#include "AnimationSetting.h"
#include "SpriteSheetSetting.h"
#include "StringUtil.h"

CharacterSetting::CharacterSetting():m_sName(("default")), m_fSpeed(10.0f)
{

}
CharacterSetting::~CharacterSetting()
{

}

void CharacterSetting::SetName( const tstring& name )
{
	std::string stdstring;
	StringUtil::Copyto(stdstring, name);
	m_sName = stdstring;
}

const string& CharacterSetting::GetName() const
{
	return m_sName;
}

void CharacterSetting::SetSpeed( float speed )
{
	m_fSpeed = speed;
}

float CharacterSetting::GetSpeed() const
{
	return m_fSpeed;
}

void CharacterSetting::AddAnimation( AnimationSetting* animsetting )
{
	m_mapAnimationSettings.insert( std::make_pair(animsetting->GetAnimationName(), animsetting) );
}

void CharacterSetting::SetStartAnimation( const tstring& startanimation )
{
	m_sStartAnimation = startanimation;
}


const tstring& CharacterSetting::GetStartAnimation() const
{
	return m_sStartAnimation;
}

void CharacterSetting::SetSpriteSheetSetting(SpriteSheetSetting* setting)
{
	m_pSpriteSheetSetting = setting;
}

const SpriteSheetSetting* CharacterSetting::GetSpriteSheetSetting() const
{
	return m_pSpriteSheetSetting;
}

const AnimationSetting* CharacterSetting::GetAnimationByName(tstring name) const
{
	return(*m_mapAnimationSettings.find(name)).second;
}