//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUI
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "IntroScreenGUI.h"
#include "GameManager.h"
#include "MyGameDefines.h"

IntroScreenGUI::IntroScreenGUI():m_pGui(0),m_pSprCursor(0)
{

}

IntroScreenGUI::~IntroScreenGUI()
{
	// Delete created objects and free loaded resources
	delete m_pGui;
	/*delete fnt;*/
	delete m_pSprCursor;
	/*hge->Effect_Free(snd);*/
	GAME_ENGINE->Texture_Free(m_TextureCursor);
}

void IntroScreenGUI::Init()
{
	m_pGui=new hgeGUI();
	CreateControls();
}

void IntroScreenGUI::CreateControls()
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

bool IntroScreenGUI::Update(float dTime)
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
		switch(lastid)
		{
		case 1:
			{
				int kak = 0;
				break;
			}
		
		case 2:
			{
				int kak2 = 1;
				break;
			}
		case 3:
		case 4:
			{
				m_pGui->SetFocus(1);
				m_pGui->Enter();
			}
		break;

		case 5: return true;
		}
	}

	else if(id) { lastid=id; m_pGui->Leave(); }

	return true;
}

bool IntroScreenGUI::Render()
{
	m_pGui->Render();
	return true;
}