//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionItemInfo
//							  Date: 24/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "CollisionItemInfo.h"
#include "ItemInfo.h"

CollisionItemInfo::CollisionItemInfo(){

}
CollisionItemInfo::~CollisionItemInfo(){

}

void CollisionItemInfo::AddItemInfo( ItemInfo* iteminfo )
{
	m_vItemInfo.push_back(iteminfo);
}

const std::vector<ItemInfo*>& CollisionItemInfo::GetItemInfos() const
{
	return m_vItemInfo;
}

void CollisionItemInfo::SetName( const string& name )
{
	m_sName = name;
}

const string& CollisionItemInfo::GetName() const
{
	return m_sName;
}