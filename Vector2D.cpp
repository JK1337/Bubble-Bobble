//******************************************************************************************
//							Author: Allaert Mathieu
//							 Class: Vector2D
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "Vector2D.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
	os << " " << rhs.x << " " << rhs.y;

	return os;
}


std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
	is >> lhs.x >> lhs.y;
	return is;
}
