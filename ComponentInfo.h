//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ComponentInfo
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef COMPONENTINFO_H_INCLUDED
#define COMPONENTINFO_H_INCLUDED
#include <vector>
class ItemInfo;

class ComponentInfo {
public:
	ComponentInfo();
	virtual ~ComponentInfo();
	void AddItemInfo(ItemInfo* item);
	void SetName(string naam);
	void SetId(int id);
	const string& GetName() const;
	int GetId() const;
	const std::vector<ItemInfo*>& GetItemInfos() const;
private:
	std::vector<ItemInfo*> m_vItems;
	string m_sName;
	int m_iId;
	ComponentInfo(const ComponentInfo& t);
	ComponentInfo& operator=(const ComponentInfo& t);
};

#endif