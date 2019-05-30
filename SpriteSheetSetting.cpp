//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: SpriteSheetSetting
//							  Date: 13/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "SpriteSheetSetting.h"

SpriteSheetSetting::SpriteSheetSetting():m_sType(_T("")){

}
SpriteSheetSetting::~SpriteSheetSetting(){

}

float SpriteSheetSetting::GetHeight() const
{
	return m_fRowHeight;
}

float SpriteSheetSetting::GetWidth() const
{
	return m_fRowWidth;
}

float SpriteSheetSetting::GetMidX() const
{
	return m_fMidX;
}

float SpriteSheetSetting::GetMidY() const
{
	return m_fMidY;
}

void SpriteSheetSetting::SetRowHeight( float rowheight )
{
	m_fRowHeight = rowheight;
}

void SpriteSheetSetting::SetRowWidth( float rowwidth )
{
	m_fRowWidth = rowwidth;
}

void SpriteSheetSetting::SetMidX( float midx )
{
	m_fMidX = midx;
}

void SpriteSheetSetting::SetMidY( float midy )
{
	m_fMidY = midy;
}

void SpriteSheetSetting::SetType(tstring type)
{
	m_sType = type;
}

const tstring& SpriteSheetSetting::GetType() const
{
	return m_sType;
}