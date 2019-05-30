//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ToolArrow
//							  Date: 24/7/2009
//******************************************************************************************

#ifndef TOOLARROW_H_INCLUDED
#define TOOLARROW_H_INCLUDED
#include "BaseEntity.h"
#include "hge.h"
#include "hgeguictrls.h"
#include "Vector2D.h"

class ToolComponent;

class ToolArrow : public hgeGUIObject, public BaseEntity
{
public:
	ToolArrow(int newid,double x, double y, double width, double height, ToolComponent* parent, bool bForward);
	virtual ~ToolArrow();
	virtual bool MouseLButton( bool bDown );
	virtual void	Render();
private:
	ToolComponent* m_pParent;
	bool m_bForward;
	ToolArrow(const ToolArrow& t);
	ToolArrow& operator=(const ToolArrow& t);
};

#endif