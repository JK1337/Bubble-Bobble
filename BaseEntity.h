//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: BaseEntity
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef BASEENTITY_H_INCLUDED
#define BASEENTITY_H_INCLUDED

#include "hge.h"
#include "hgeanim.h"
#include "Vector2D.h"



class BaseEntity {
public:
	BaseEntity(double xPos, double yPos, double width, double height);
	BaseEntity(Vector2D position,double width, double height);
	virtual void Init(const string& spritename);
	virtual bool Draw();
	virtual bool Tick(float dTime);
	virtual ~BaseEntity();
	hgeSprite* GetSprite();

protected:
	hgeSprite*			m_pSpr;
	void LoadTexture(const string& texname);
	void LoadTextureWH(const string& textname, float width, float height);
	string m_sName;
	HTEXTURE m_Tex;
	Vector2D m_vPosition;
	double m_dWidth;
	double m_dHeight;
	
	

private:

	

	
	BaseEntity(const BaseEntity& t);
	BaseEntity& operator=(const BaseEntity& t);
	
};
//CHAR wide_to_narrow(WCHAR w);
#endif