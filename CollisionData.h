//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionData
//							  Date: 27/7/2009
//******************************************************************************************

#ifndef COLLISIONDATA_H_INCLUDED
#define COLLISIONDATA_H_INCLUDED

#include "ItemData.h"


class CollisionData : public ItemData
{
public:
	CollisionData();
	virtual ~CollisionData();
	float GetAantalMid() const;
	virtual void SetAantalWidth(float width);
private:
	float m_fWidth;
	CollisionData(const CollisionData& t);
	CollisionData& operator=(const CollisionData& t);
};

#endif