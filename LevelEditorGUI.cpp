//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUI
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "LevelEditorGUI.h"
#include "GameManager.h"
#include "MyGameDefines.h"
#include "Toolbar.h"
#include "GuiSettings.h"
#include "LevelEditor.h"
#include <algorithm>
LevelEditorGUI* LevelEditorGUI::m_pLevelEditorGUI = NULL;

LevelEditorGUI::LevelEditorGUI():m_pGui(0),m_pSprCursor(0)
{

}

LevelEditorGUI::~LevelEditorGUI()
{
	// Delete created objects and free loaded resources
	delete m_pGui;
	/*delete fnt;*/
	delete m_pSprCursor;
	/*hge->Effect_Free(snd);*/
	GAME_ENGINE->Texture_Free(m_TextureCursor);
}

void LevelEditorGUI::Init(GuiSettings* guisettings, LevelEditor* editor)
{
	m_pGui=new hgeGUI();
	//maak toolbar aan
	m_pToolbar = new Toolbar(guisettings, 500, 102,editor);
	m_pToolbar->Init();
	//maak overige controls aan
	CreateControls(guisettings);
}

void LevelEditorGUI::CreateControls(GuiSettings* guisettings)
{
	string sArtPath = GameManager::GetSingleton()->GetArtPath();

	//laad controls in


	//voeg ze toe aan de gui
	string cursorpath = sArtPath + "Cursor/cursor.png";
	//laad cursor in
	m_TextureCursor =  GAME_ENGINE->Texture_Load(cursorpath.c_str());
	m_pSprCursor = new hgeSprite(m_TextureCursor,0,0,32,32);

	//instellingen van de gui
	m_pGui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	m_pGui->SetCursor(m_pSprCursor);
	m_pGui->SetFocus(1);
	m_pGui->Enter();
}

bool LevelEditorGUI::Update(float dTime)
{
	int id;
	static int lastid=0;

	// If ESCAPE was pressed, tell the GUI to finish
	if(GAME_ENGINE->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; m_pGui->Leave(); }


	// We update the GUI and take an action if
	// one of the menu items was selected
	id=m_pGui->Update(dTime);

	if(id == -1)
	{
// 		switch(lastid)
// 		{
// 		case 1:
// 			m_pGui->SetFocus(1);
// 			m_pGui->Enter();
// 		break;
// 		case 2:
// 			m_pGui->SetFocus(2);
// 			m_pGui->Enter();
// 			break;
// 		case 3:
// 			m_pGui->SetFocus(3);
// 			m_pGui->Enter();
// 		break;
// 		case 4:
// 			m_pGui->SetFocus(4);
// 			m_pGui->Enter();
// 		break;
// 
// 		case 5: return true;
// 		}
		m_pGui->SetFocus(lastid);
		m_pGui->Enter();
	}

	

	else if(id) { lastid=id; m_pGui->Leave(); }

	CheckItemsToDelete();

	return true;
}

bool LevelEditorGUI::Render()
{
	m_pGui->Render();
	return true;
}

LevelEditorGUI* LevelEditorGUI::GetSingleton()
{
	if(m_pLevelEditorGUI == NULL)
	{
		m_pLevelEditorGUI = new LevelEditorGUI();
		//m_pLevelEditor->Init();
	}

	return m_pLevelEditorGUI;
}

void LevelEditorGUI::RegisterNewButton(hgeGUIObject* object)
{
	m_pGui->AddCtrl(object);
}

void LevelEditorGUI::RemoveButton(int buttonid)
{
	m_vItemsToDelete.push_back(buttonid);
}

void LevelEditorGUI::HideButton(int buttonid)
{
	m_pGui->ShowCtrl(buttonid, false);
}

void LevelEditorGUI::MoveItem(int id, float dx, float dy)
{
	m_pGui->MoveCtrl(id, dx, dy);
}

hgeGUIObject* LevelEditorGUI::GetComponentById(int id)
{
	return m_pGui->GetCtrl(id);
}

class FDeleteControl
{
public:
	FDeleteControl(hgeGUI* gui):m_pGui(gui){};
	void operator()(int todelete)
	{
		m_pGui->DelCtrl(todelete);
	}

private:
	hgeGUI* m_pGui;
};

void LevelEditorGUI::CheckItemsToDelete()
{
	if(m_vItemsToDelete.size() > 0)
	{
		for_each(m_vItemsToDelete.begin(), m_vItemsToDelete.end(), FDeleteControl(m_pGui));
	}
	m_vItemsToDelete.clear();
	m_pGui->Reset();
}

const string& LevelEditorGUI::GetSelectedCategoryName() const
{
	return m_pToolbar->GetSelectedCategoryName();
}

/*
hgeGUI* LevelEditorGUI::GetGUI()
{
	return m_pGui;
}
*/ 