//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionEntity
//							  Date: 28/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "CollisionEntity.h"
#include "CollisionData.h"

CollisionEntity::CollisionEntity(int x, int y, int width, int height, const CollisionData* data):BaseEntity(x, y, width, height), m_pCollisionData(data), m_bDraw(true)
{

}

CollisionEntity::CollisionEntity(int x, int y, int width, int height):BaseEntity(x, y, width, height), m_bDraw()
{
	
}

CollisionEntity::~CollisionEntity(){

}

void CollisionEntity::InitCollisionItem(InitCollisionItemStruct ItemStruct, const string& pathtofile1, const string& pathtofile2, const string& pathtofile3)
{
	LoadTextureWH(pathtofile1, ItemStruct.width1, ItemStruct.height1);
	m_vSprites.push_back(m_pSpr);
	m_dWidth = m_pSpr->GetWidth();
	LoadTextureWH(pathtofile2, ItemStruct.width2, ItemStruct.height2);
	m_vSprites.push_back(m_pSpr);
	m_dWidth += m_pCollisionData->GetAantalMid() * m_pSpr->GetWidth();
	LoadTextureWH(pathtofile3, ItemStruct.width3, ItemStruct.height3);
	m_vSprites.push_back(m_pSpr);
	m_dWidth += m_pSpr->GetWidth();
}

bool CollisionEntity::Draw()
{
	if(m_bDraw)
	{
		float xPosition = static_cast<float>(m_vPosition.x);
		float yPosition = static_cast<float>(m_vPosition.y);

		//draw eerste block
		m_vSprites.at(0)->Render(xPosition, yPosition);
		xPosition += m_vSprites.at(0)->GetWidth();

		//draw middenste blokken
		for(int i= 0; i<m_pCollisionData->GetAantalMid(); ++i)
		{
			m_vSprites.at(1)->Render(xPosition, yPosition);
			xPosition += m_vSprites.at(1)->GetWidth();
		}

		//draw laatste blok
		m_vSprites.at(2)->Render(xPosition, yPosition);

		return true;
	}
}

RECT CollisionEntity::GetRect()
{
	RECT rect;
	rect.top = m_vPosition.y;
	rect.left = m_vPosition.x;
	rect.right = m_vPosition.x + m_dWidth;
	rect.bottom = m_vPosition.y + m_dHeight;
	return rect;
}

