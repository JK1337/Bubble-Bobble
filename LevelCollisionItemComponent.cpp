//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelCollisionItem
//							  Date: 26/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "LevelCollisionItemComponent.h"
#include <algorithm>

LevelCollisionItemComponent::LevelCollisionItemComponent(int newid,float x, float y, InitCollisionItemStruct initstruct, LevelEditor* editor, bool bCollision):
														LevelItem(newid, x, y, (initstruct.width1+initstruct.width2+initstruct.width3)
															,(initstruct.height1), editor,bCollision), m_pItemStruct(initstruct)
{

}
LevelCollisionItemComponent::~LevelCollisionItemComponent()
{

}

void LevelCollisionItemComponent::InitCollisionItem(const string& path1, const string& path2, const string& path3)
{
	//we laden de 3 delen van onze textuur in
	//de minimum breedte van onze plane is de grootte
	//van één collisionblokje
	LoadTextureWH(path1, m_pItemStruct.width1, m_pItemStruct.height1);
	m_vSprites.push_back(m_pSpr);
	m_fMinimumPlaneWidth = m_pSpr->GetWidth();
	LoadTextureWH(path2, m_pItemStruct.width2, m_pItemStruct.height2);
	m_vSprites.push_back(m_pSpr);
	m_fMinimumPlaneWidth += m_pSpr->GetWidth();
	LoadTextureWH(path3, m_pItemStruct.width3, m_pItemStruct.height3);
	m_vSprites.push_back(m_pSpr);
	m_fMinimumPlaneWidth += m_pSpr->GetWidth();
	//onze huidige size blijft 0 want standaard hebben we nog niet gedragged
	m_fCurrentSize = m_fMinimumPlaneWidth;
	//m_pSpr->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND);
	/*m_pSpr->SetBlendMode(BLEND_COLORADD | BLEND_ALPHABLEND);
	m_pSpr->SetColor(0xFF000000,0);
	m_pSpr->SetColor(0xFF000000,1);
	m_pSpr->SetColor(0xFF000040,2);
	m_pSpr->SetColor(0xFF000040,3);*/

}	



void LevelCollisionItemComponent::Render()
{
	//Check hoe breedt hij uiteindelijk is geworden
	if(m_fMinimumPlaneWidth > m_fCurrentSize)
		DrawOne();
	else
		DrawMultiple();
}

class FDrawOneBlock
{
public:
	FDrawOneBlock(Vector2D position):m_vPosition(position),m_fxOffset(0){};
	void operator()(hgeSprite* sprite)
	{
		sprite->Render(static_cast<float>(m_vPosition.x + m_fxOffset),static_cast<float>(m_vPosition.y));
		m_fxOffset += sprite->GetWidth();
	}

private:
	Vector2D m_vPosition;
	float m_fxOffset;
};

void LevelCollisionItemComponent::DrawOne()
{
	for_each(m_vSprites.begin(), m_vSprites.end(), FDrawOneBlock(m_vPosition));
}

void LevelCollisionItemComponent::DrawMultiple()
{
	
	float xPosition = static_cast<float>(m_vPosition.x);
	float yPosition = static_cast<float>(m_vPosition.y);

	//draw eerste block
	m_vSprites.at(0)->Render(xPosition, yPosition);
	xPosition += m_vSprites.at(0)->GetWidth();

	//draw middenste blokken
	for(int i= 0; i<m_iCurrentMidAantal; ++i)
	{
		m_vSprites.at(1)->Render(xPosition, yPosition);
		xPosition += m_vSprites.at(1)->GetWidth();
	}

	//draw laatste blok
	m_vSprites.at(2)->Render(xPosition, yPosition);

}

int LevelCollisionItemComponent::BerekenAantalMid()
{
	//de breedte van de middenste blokken zijn altijd
	//de totale breedte - (breedte begin + eind)
	float difwidth = (m_vSprites.at(0)->GetWidth() + m_vSprites.at(2)->GetWidth());
	float midblockswidth = m_fCurrentSize - difwidth;

	//we moeten midblockwidth nog afronden naar boven om altijd een volledig blokje te tekenen
	float widthblock = m_vSprites.at(1)->GetWidth();

	return static_cast<int>(ceil(midblockswidth/widthblock));
}	

void LevelCollisionItemComponent::EditingSize(float dx)
{
	m_fCurrentSize += dx;

	//update rect
	if(m_fCurrentSize > m_fMinimumPlaneWidth)
	{
		//we hebben meer mid blokjes hier
		m_iCurrentMidAantal = BerekenAantalMid();
		rect.Set(m_vPosition.x, m_vPosition.y, m_vPosition.x + m_fCurrentSize, m_vPosition.y + m_dHeight);
	}
		
	else
	{
		m_iCurrentMidAantal = 1;
		rect.Set(m_vPosition.x, m_vPosition.y, m_vPosition.x + m_fMinimumPlaneWidth, m_vPosition.y + m_dHeight);
	}
}

void LevelCollisionItemComponent::UpdateRect()
{

}

string LevelCollisionItemComponent::Save()
{
	std::stringstream mystream;
	mystream << "<CollisionItem name=\"" << GetName() << "\" x=\"" << 
		m_vPosition.x << "\" y=\"" 
		<< m_vPosition.y << "\" aantalMid=\"" 
		<< m_iCurrentMidAantal << "\" width=\"" 
		<< m_dWidth << "\" height=\"" 
		<< m_dHeight << "\"" << "/>";
	return mystream.str();
}