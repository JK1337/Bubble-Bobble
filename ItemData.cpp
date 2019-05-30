//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ItemData
//							  Date: 27/7/2009
//******************************************************************************************

#include "ItemData.h"

ItemData::ItemData(){

}
ItemData::~ItemData(){

}

void ItemData::SetName( const string& name )
{
	m_sName = name;
}

const string& ItemData::GetName() const
{
	return m_sName;
}

void ItemData::SetX( float x )
{
	m_fX = x;
}

float ItemData::GetX() const
{
	return m_fX;
}

void ItemData::SetY( float y )
{
	m_fY = y;
}

float ItemData::GetY() const
{
	return m_fY;
}

void ItemData::SetWidth( float width )
{
	m_fWidth = width;
}

float ItemData::GetWidth() const
{
	return m_fWidth;
}

void ItemData::SetHeight( float height )
{
	m_fHeight = height;
}

float ItemData::GetHeight() const
{
	return m_fHeight;
}