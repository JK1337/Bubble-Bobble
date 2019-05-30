//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ItemData
//							  Date: 27/7/2009
//******************************************************************************************

#ifndef ITEMDATA_H_INCLUDED
#define ITEMDATA_H_INCLUDED


#include "stdafx.h"

class ItemData {
public:
	ItemData();
	virtual ~ItemData();
	virtual void SetName(const string& name);
	virtual const string& GetName() const;
	virtual void SetX(float x);
	virtual float GetX() const;
	virtual void SetY(float y);
	virtual float GetY() const;
	virtual void SetWidth(float width);
	virtual float GetWidth() const;
	virtual void SetHeight(float height);
	virtual float GetHeight() const;

private:

	string m_sName;
	float m_fX;
	float m_fY;
	float m_fWidth;
	float m_fHeight;

	ItemData(const ItemData& t);
	ItemData& operator=(const ItemData& t);
};

#endif