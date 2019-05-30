//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: StringUtil
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef STRINGUTIL_H_INCLUDED
#define STRINGUTIL_H_INCLUDED



class StringUtil {
public:

	static void Copyto(std::string& l,const std::wstring& r);
	
private:

	StringUtil();
	virtual ~StringUtil();

	
	StringUtil(const StringUtil& t);
	StringUtil& operator=(const StringUtil& t);
};

#endif