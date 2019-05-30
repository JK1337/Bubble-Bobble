//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: CollisionItemInfo
//							  Date: 24/7/2009
//******************************************************************************************

#ifndef COLLISIONITEMINFO_H_INCLUDED
#define COLLISIONITEMINFO_H_INCLUDED

class ItemInfo;
#include <vector>

class CollisionItemInfo {
public:
	CollisionItemInfo();
	virtual ~CollisionItemInfo();
	void AddItemInfo(ItemInfo* iteminfo);
	const std::vector<ItemInfo*>& GetItemInfos() const;
	void SetName(const string& name);
	const string& GetName() const;

private:

	std::vector<ItemInfo*> m_vItemInfo;
	string m_sName;
	CollisionItemInfo(const CollisionItemInfo& t);
	CollisionItemInfo& operator=(const CollisionItemInfo& t);
};

#endif