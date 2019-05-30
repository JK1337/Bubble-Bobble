//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ItemInfo
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef ITEMINFO_H_INCLUDED
#define ITEMINFO_H_INCLUDED


#include "stdafx.h"


class ItemInfo {
public:
	ItemInfo();
	virtual ~ItemInfo();
	void SetId(int id);
	void SetNaam(string naam);
	int GetId() const;
	const string& GetNaam() const;
private:
	int m_iId;
	string m_sNaam;
	ItemInfo(const ItemInfo& t);
	ItemInfo& operator=(const ItemInfo& t);
};

#endif