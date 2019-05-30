//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelItem
//							  Date: 24/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "LevelItem.h"
#include "LevelEditorGUI.h"
#include "LevelEditor.h"
LevelItem::LevelItem(int newid, float x, float y, float width, float height, LevelEditor* editor, bool bCollision):m_pParent(editor), m_bCollisionItem(bCollision),
																				BaseEntity(x,y,width,height)
{
	bStatic=false; bVisible=true; bEnabled=true;
	id = newid;
	rect.Set(x, y, x+width, y+height);
}
LevelItem::~LevelItem(){
	int kak = 0;
}

void LevelItem::Move( float dx, float dy )
{
	m_vPosition.x += dx;
	m_vPosition.y += dy;
	
	//move hem ook nog in de gui zodat de rect / clickarea hopelijk mee
	//beweegt
	//LevelEditorGUI::GetSingleton()->MoveItem(this->id, dx, dy);
	
	rect.Set(static_cast<float>(m_vPosition.x), static_cast<float>(m_vPosition.y), static_cast<float>(m_vPosition.x + m_dWidth) ,static_cast<float>(m_vPosition.y+m_dHeight));
}

void LevelItem::Render()
{
	m_pSpr->Render(static_cast<float>(m_vPosition.x),static_cast<float>(m_vPosition.y));
}

bool LevelItem::MouseLButton( bool bDown )
{
	if(!bDown)
	{

		return true;
	}
	else 
	{
		m_pParent->LevelItemSelected(this);
		

		return false;
	}
}


int LevelItem::GetId()
{
	return id;
}

bool LevelItem::IsCollisionItem()
{
	return m_bCollisionItem;
}

string LevelItem::Save()
{
	std::stringstream mystream;
	mystream << "<levelItem name=\"" << GetName() 
		<< "\" x=\"" << m_vPosition.x 
		<< "\" y=\"" << m_vPosition.y 
		<< "\" width=\"" << m_dWidth 
		<< "\" height=\"" << m_dHeight
		<< "\"" << " />";
	return mystream.str();
}

void LevelItem::SetName(const string& name)
{
	m_sName = name;
}

const string& LevelItem::GetName()
{
	return m_sName;
}