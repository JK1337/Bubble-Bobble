//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ToolArrow
//							  Date: 24/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "ToolArrow.h"
#include "MyGameDefines.h"
#include "ToolComponent.h"

ToolArrow::ToolArrow(int newid,double x, double y, double width, double height, ToolComponent* parent, bool bForward)
										:BaseEntity(x,y, width,height),
										m_pParent(parent), m_bForward(bForward)
{
	bStatic=false; bVisible=true; bEnabled=true;
	id = newid;
	rect.Set(x, y, x+width, y+height);
}
ToolArrow::~ToolArrow(){
	delete m_pSpr;
	GAME_ENGINE->Texture_Free(m_Tex);
}



bool ToolArrow::MouseLButton( bool bDown )
{
	if(!bDown)
	{

		return true;
	}
	else 
	{
		m_pParent->ChooseNewItem(m_bForward);
		//hge->Effect_Play(snd);
		//offset=0;

		return false;
	}
}

void ToolArrow::Render()
{
	m_pSpr->Render(m_vPosition.x,m_vPosition.y);
}