//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: EnemyItem
//							  Date: 24/8/2009
//******************************************************************************************

#ifndef ENEMYITEM_H_INCLUDED
#define ENEMYITEM_H_INCLUDED


#include "stdafx.h"
#include "LevelItem.h"
class EnemyItem : public LevelItem {
public:
	EnemyItem(int newid, float x, float y, float width, float height, LevelEditor* editor, bool bCollision);
	virtual ~EnemyItem();
	virtual string Save();
private:

	EnemyItem(const EnemyItem& t);
	EnemyItem& operator=(const EnemyItem& t);
};

#endif