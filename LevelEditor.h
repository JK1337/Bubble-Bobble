//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelEditor
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef LEVELEDITOR_H_INCLUDED
#define LEVELEDITOR_H_INCLUDED

class GuiSettings;
class LevelItem;
#include "hge.h"
#include <vector>
class LevelEditor {
public:
	LevelEditor(GuiSettings* guisettings);
	virtual ~LevelEditor();
	void Init();
	bool Update(float dTime);
	bool Render();
	void CreateNewLevelObject(const std::string& objectname);
	void LevelItemSelected(LevelItem* levelitem);

private:
	bool m_bItemSelected;
	GuiSettings* m_pGuiSettings;
	float m_mouseX, m_mouseY;
	float m_mouseOldX, m_mouseOldY;
	bool m_bCreated, m_bCollisionEditing;
	LevelItem* m_pCurrentLevelItemSelected;
	std::vector<int> m_vLevelItems;
	hgeQuad m_quad;
	LevelEditor(const LevelEditor& t);
	LevelEditor& operator=(const LevelEditor& t);
	bool HandleMouseUp(hgeInputEvent event);
	void HandleLeftClicked(hgeInputEvent event);
	void HandleRightClicked(hgeInputEvent event);
	void DragItem();
	int GetUniqueLevelId();
	void CheckKey(hgeInputEvent event);
	void CheckItemsToDelete();
	void PlaatsItem();
	bool HandleMouseDown(hgeInputEvent event);
	void InitQuad();

	void WriteXML();
	void ResetSelected();
	void CreateCollisionItem(const std::string& objectname);
	void CreateBackGroundItem(const std::string& objectname);
	void CreateEnemyItem(const std::string& objectname);
};

#endif