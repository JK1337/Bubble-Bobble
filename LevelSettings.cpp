//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelSettings
//							  Date: 27/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "LevelSettings.h"
#include "LevelData.h"
LevelSettings::LevelSettings(){

}

LevelSettings::~LevelSettings(){

}

void LevelSettings::AddLevelData( LevelData* data )
{
	m_vLevelData.push_back(data);
}

const LevelData* LevelSettings::GetLevelData( UINT levelindex ) const
{
	if(levelindex >= m_vLevelData.size())
	{
		//should not come here assert
		int a = 0;
		return 0;
	}
		
	else
		return m_vLevelData.at(levelindex);
}
const LevelData* LevelSettings::GetLastMAde() const
{
	return m_vLevelData.at(m_vLevelData.size()-1);
}