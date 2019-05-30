//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelCollisionItemComponent
//							  Date: 26/7/2009
//******************************************************************************************

#ifndef LevelCollisionItemComponent_H_INCLUDED
#define LevelCollisionItemComponent_H_INCLUDED



#include "LevelItem.h"

struct InitCollisionItemStruct
{
	float width1;
	float height1;
	float width2;
	float height2;
	float width3;
	float height3;
};

class LevelCollisionItemComponent: public LevelItem {
public:
	LevelCollisionItemComponent(int newid, float x, float y, InitCollisionItemStruct initstruct, LevelEditor* editor, bool bCollision);
	virtual ~LevelCollisionItemComponent();
	
	void InitCollisionItem(const string& path1, const string& path2, const string& path3);
	virtual void	Render();
	void EditingSize(float dx);
	string Save();

private:
	vector<hgeSprite*> m_vSprites;
	float m_fMinimumPlaneWidth;
	float m_fCurrentSize;
	int m_iCurrentMidAantal;

	void UpdateRect();
	void DrawOne();
	void DrawMultiple();
	int BerekenAantalMid();

	InitCollisionItemStruct m_pItemStruct;

	LevelCollisionItemComponent(const LevelCollisionItemComponent& t);
	LevelCollisionItemComponent& operator=(const LevelCollisionItemComponent& t);
	
};

#endif