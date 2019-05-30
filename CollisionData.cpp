//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionData
//							  Date: 27/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "CollisionData.h"

CollisionData::CollisionData(){

}
CollisionData::~CollisionData(){

}

float CollisionData::GetAantalMid() const
{
	return m_fWidth;
}

void CollisionData::SetAantalWidth( float width )
{
	m_fWidth = width;
}