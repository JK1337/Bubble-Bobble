//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ComponentInfo
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "ComponentInfo.h"
#include "ItemInfo.h"


ComponentInfo::ComponentInfo(){

}
ComponentInfo::~ComponentInfo(){

}

void ComponentInfo::AddItemInfo( ItemInfo* item )
{
	m_vItems.push_back(item);
}

const std::vector<ItemInfo*>& ComponentInfo::GetItemInfos() const
{
	return m_vItems;
}

void ComponentInfo::SetName( string naam )
{
	m_sName = naam;
}

void ComponentInfo::SetId( int id )
{
	m_iId = id;
}

const string& ComponentInfo::GetName() const
{
	return m_sName;
}

int ComponentInfo::GetId() const
{
	return m_iId;
}