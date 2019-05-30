//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: InGameGUI
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "InGameGUI.h"
#include "GameManager.h"
#include "MyGameDefines.h"

InGameGUI::InGameGUI():m_pInGameGUI(0),m_pSprCursor(0)
{

}

InGameGUI::~InGameGUI()
{
	// Delete created objects and free loaded resources
	delete m_pInGameGUI;
	/*delete fnt;*/
	delete m_pSprCursor;
	/*hge->Effect_Free(snd);*/
	GAME_ENGINE->Texture_Free(m_TextureCursor);
}

void InGameGUI::Init()
{
	m_pInGameGUI=new hgeGUI();
	CreateControls();
}

void InGameGUI::CreateControls()
{
	string sArtPath = GameManager::GetSingleton()->GetArtPath();

	//laad controls in
	

	//voeg ze toe aan de InGameGUI
	string cursorpath = sArtPath + "Cursor/cursor.png";
	//laad cursor in
	m_TextureCursor =  GAME_ENGINE->Texture_Load(cursorpath.c_str());
	m_pSprCursor = new hgeSprite(m_TextureCursor,0,0,32,32);

	//instellingen van de InGameGUI
	m_pInGameGUI->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	m_pInGameGUI->SetCursor(m_pSprCursor);
	m_pInGameGUI->SetFocus(1);
	m_pInGameGUI->Enter();
}

bool InGameGUI::Update(float dTime)
{
	int id;
	static int lastid=0;

	// If ESCAPE was pressed, tell the InGameGUI to finish
	if(GAME_ENGINE->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; m_pInGameGUI->Leave(); }

	// We update the InGameGUI and take an action if
	// one of the menu items was selected
	id=m_pInGameGUI->Update(dTime);

	if(id == -1)
	{
		switch(lastid)
		{
		case 1:

		case 2:
		case 3:
		case 4:
			m_pInGameGUI->SetFocus(1);
			m_pInGameGUI->Enter();
		break;

		case 5: return true;
		}
	}

	else if(id) { lastid=id; m_pInGameGUI->Leave(); }

	return true;
}

bool InGameGUI::Render()
{
	m_pInGameGUI->Render();
	return true;
}