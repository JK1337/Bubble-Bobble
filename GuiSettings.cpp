//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameSettings
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "GuiSettings.h"
#include "ComponentInfo.h"
#include <algorithm>
#include "CollisionItemInfo.h"

GuiSettings::GuiSettings()
{

}

template<typename T>
void DeleteThatShit(T element)
{
	delete element;
	element = NULL;
}

GuiSettings::~GuiSettings()
{
	//delete alle infos
	for_each(m_vComponentInfos.begin(), m_vComponentInfos.end(), DeleteThatShit<ComponentInfo*>);
}

void GuiSettings::AddComponentInfo( ComponentInfo* info )
{
	m_vComponentInfos.push_back(info);
}

const vector<ComponentInfo*>& GuiSettings::GetAllComponentInfo()
{
	return m_vComponentInfos;
}

void GuiSettings::AddCollisionItem( CollisionItemInfo* info )
{
	m_mapCollisionItems.insert(std::make_pair(info->GetName(), info));
}