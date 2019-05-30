//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: StringUtil
//							  Date: 13/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "StringUtil.h"

StringUtil::StringUtil(){

}
StringUtil::~StringUtil(){

}

void StringUtil::Copyto( std::string& l,const std::wstring& r )
{
	size_t i = 0;
	const size_t n = r.length()+1;
	l.resize(n); // make sure we have enough
	for(;i<n;++i)
	{
		l[i] = r[i];
	}
	l[i] = 0;
	l.resize(n-1);
}