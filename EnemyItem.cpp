//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyItem
//							  Date: 24/8/2009
//******************************************************************************************

#include "EnemyItem.h"

EnemyItem::EnemyItem(int newid, float x, float y, float width, float height, LevelEditor* editor, bool bCollision):LevelItem(newid, x, y, width, height, editor, bCollision){

}
EnemyItem::~EnemyItem(){

}

string EnemyItem::Save()
{
	std::stringstream mystream;
	mystream << "<enemyItem name=\"" << GetName() 
		<< "\" x=\"" << m_vPosition.x 
		<< "\" y=\"" << m_vPosition.y 
		<< "\" width=\"" << m_dWidth 
		<< "\" height=\"" << m_dHeight
		<< "\"" << " />";
	return mystream.str();
}