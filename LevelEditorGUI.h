//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUI
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef LevelEditorGUI_H_INCLUDED
#define LevelEditorGUI_H_INCLUDED

#include "..\include\hge.h"
#include "..\include\hgegui.h"

#include <vector>

class GuiSettings;
class Toolbar;
class LevelEditor;
class LevelEditorGUI {
public:
	
	virtual ~LevelEditorGUI();
	void Init(GuiSettings* guisettings, LevelEditor* editor);
	bool Update(float dTime);
	bool Render();
	static LevelEditorGUI* GetSingleton();
	void RegisterNewButton(hgeGUIObject* object);
	void RemoveButton(int buttonid);
	void MoveItem(int id, float dx, float dy);
	void HideButton(int buttonid);
	const string& GetSelectedCategoryName() const;
	hgeGUIObject* GetComponentById(int id);
	//hgeGUI* GetGUI();
private:
	LevelEditorGUI();
	static LevelEditorGUI* m_pLevelEditorGUI;

	hgeGUI     *m_pGui;
	hgeSprite  *m_pSprCursor;
	HTEXTURE   m_TextureCursor;
	Toolbar* m_pToolbar;

	vector<int>m_vItemsToDelete;

	LevelEditorGUI(const LevelEditorGUI& t);
	LevelEditorGUI& operator=(const LevelEditorGUI& t);

	void CreateControls(GuiSettings* guisettings);
	void CheckItemsToDelete();
	

};

#endif