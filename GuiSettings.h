//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GameSettings
//							  Date: 13/7/2009
//******************************************************************************************

#ifndef GUISETTINGS_H_INCLUDED
#define GUISETTINGS_H_INCLUDED


#include <vector>
#include <map>
class CollisionItemInfo;
using namespace std;

class ComponentInfo;

class GuiSettings {
public:
	GuiSettings();
	virtual ~GuiSettings();
	void AddComponentInfo(ComponentInfo* info);
	const std::vector<ComponentInfo*>& GetAllComponentInfo();
	void AddCollisionItem(CollisionItemInfo* info);

private:

	GuiSettings(const GuiSettings& t);
	GuiSettings& operator=(const GuiSettings& t);
	
	std::vector<ComponentInfo*> m_vComponentInfos;
	typedef std::map<string, CollisionItemInfo*> CollisionMap;
	CollisionMap m_mapCollisionItems;

};

#endif