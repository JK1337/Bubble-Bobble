//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionHelperClass
//							  Date: 20/8/2009
//******************************************************************************************

#ifndef CollisionHelperClass_H_INCLUDED
#define CollisionHelperClass_H_INCLUDED


//enum EnumInterSection
//{
//	DONT_INTERSECT = 0,
//	COLLINEAR = 1,
//	DO_INTERSECT = 2
//};

#include "Vector2D.h"

class CollisionHelperClass {
public:
	
	static Vector2D CheckIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	static bool CheckRectangleCollisions(const RECT& rectA, const RECT& rectB);
private:
	CollisionHelperClass();
	virtual ~CollisionHelperClass();
	CollisionHelperClass(const CollisionHelperClass& t);
	CollisionHelperClass& operator=(const CollisionHelperClass& t);
	static bool SameSign(float a, float b);
};

#endif