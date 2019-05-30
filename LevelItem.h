//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelItem
//							  Date: 24/7/2009
//******************************************************************************************

#ifndef LEVELITEM_H_INCLUDED
#define LEVELITEM_H_INCLUDED

class LevelEditor;

#include "hge.h"
#include "hgeguictrls.h"
#include "BaseEntity.h"


class LevelItem : public hgeGUIObject, public BaseEntity
{
public:
	LevelItem(int newid, float x, float y, float width, float height, LevelEditor* editor, bool bCollision);
	virtual ~LevelItem();
	virtual void	Render();
	virtual void	Move(float dx, float dy);
	virtual bool MouseLButton( bool bDown );
	virtual int GetId();
	virtual bool IsCollisionItem();
	virtual string Save();
	void SetName(const string& name);
	const string& GetName();
private:
	LevelEditor* m_pParent;
	bool m_bCollisionItem;
	string m_sName;
	
	LevelItem(const LevelItem& t);
	LevelItem& operator=(const LevelItem& t);
	

};

#endif