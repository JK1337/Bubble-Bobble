//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ItemInfo
//							  Date: 23/7/2009
//******************************************************************************************

#include "ItemInfo.h"

ItemInfo::ItemInfo(){

}
ItemInfo::~ItemInfo(){

}

void ItemInfo::SetId( int id )
{
	m_iId = id;
}

void ItemInfo::SetNaam( string naam )
{
	m_sNaam = naam;
}

int ItemInfo::GetId() const
{
	return m_iId;
}

const string& ItemInfo::GetNaam() const
{
	return m_sNaam;
}