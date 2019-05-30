//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: LevelEditor
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "LevelEditor.h"
#include "GuiSettings.h"
#include "LevelEditorGUI.h"
#include "MyGameDefines.h"
#include "LevelItem.h"
#include <algorithm>
#include "LevelCollisionItemComponent.h"
#include "MyGameDefines.h"
#include "EnemyItem.h"
LevelEditor::LevelEditor(GuiSettings* guisettings):m_pGuiSettings(guisettings), m_bItemSelected(false), m_bCreated(false), m_bCollisionEditing(false)
{
}

LevelEditor::~LevelEditor()
{
	GAME_ENGINE->Texture_Free(m_quad.tex);
}

void LevelEditor::Init()
{
	//we moeten ook een quad initten om blauwe achtergrond te tekenen

	LevelEditorGUI::GetSingleton()->Init(m_pGuiSettings, this);
	InitQuad();
}

void LevelEditor::InitQuad()
{
	float screenWidth(GameManager::GetSingleton()->GetScreenWidth());
	float screenHeight(GameManager::GetSingleton()->GetScreenHeight());
	m_quad.v[0].x=0; m_quad.v[0].y=0;
	m_quad.v[1].x=screenWidth; m_quad.v[1].y=0;
	m_quad.v[2].x=screenWidth; m_quad.v[2].y=screenHeight;
	m_quad.v[3].x=0; m_quad.v[3].y=screenHeight;

	m_quad.blend = BLEND_NOZWRITE;
	m_quad.v[0].tx=0; m_quad.v[0].ty=0; 
	m_quad.v[1].tx=1; m_quad.v[1].ty=0; 
	m_quad.v[2].tx=1; m_quad.v[2].ty=1; 
	m_quad.v[3].tx=0; m_quad.v[3].ty=1; 

	for(int i=0;i<4;i++)
	{
		m_quad.v[i].z=0.9f;
		m_quad.v[i].col=0xFFFFFFFF;
	}
	
	string sbackground = GameManager::GetSingleton()->GetArtPath() + "Levels/Achtergrond.png";
	m_quad.tex = GAME_ENGINE->Texture_Load(sbackground.c_str());
}

bool LevelEditor::Update(float dTime)
{
	m_mouseOldX = m_mouseX;
	m_mouseOldY = m_mouseY;
	GAME_ENGINE->Input_GetMousePos(&m_mouseX, &m_mouseY);
	hgeInputEvent event;
	event.type = -1;
	GAME_ENGINE->Input_GetEvent(&event);
	
	switch(event.type)
	{
		case INPUT_MBUTTONUP:
			HandleMouseUp(event);
		break;

		case INPUT_MOUSEMOVE:
			DragItem();
		break;

		case INPUT_KEYUP:
			CheckKey(event);
		break;
	}
	
	LevelEditorGUI::GetSingleton()->Update(dTime);

	m_bCreated = false;
	return true;
}


void LevelEditor::CheckKey(hgeInputEvent event)
{
	if(event.key == HGEK_S)
	{
		//saving
		WriteXML();
	}

	switch(event.key)
	{
	case HGEK_S:
		WriteXML();
	break;
	case HGEK_R:
		ResetSelected();
	break;
	}
}

void LevelEditor::DragItem()
{
	if(m_bItemSelected && ! m_bCreated)
		if(m_bCollisionEditing)
		{
			LevelCollisionItemComponent* collisionItem = dynamic_cast<LevelCollisionItemComponent*>(m_pCurrentLevelItemSelected);
			if(collisionItem != 0)
				collisionItem->EditingSize(m_mouseX-m_mouseOldX);
		} else {
			m_pCurrentLevelItemSelected->Move(m_mouseX-m_mouseOldX, m_mouseY-m_mouseOldY);
		}
}

bool LevelEditor::HandleMouseUp(hgeInputEvent event)
{
	if(m_bItemSelected && ! m_bCreated)
	{
		//check welke muis knop
		switch(event.key)
		{
		case 1:
			HandleLeftClicked(event);
		break;
		case 2:
			HandleRightClicked(event);
		break;
		} 
	}

	return true;
}

void LevelEditor::ResetSelected()
{
	m_bItemSelected = false;
	//m_bCreated = false;
}

void LevelEditor::HandleLeftClicked(hgeInputEvent event)
{
	if(m_bItemSelected && !m_bCreated)
	{
		PlaatsItem();
	}else{
		//donothing item moet nieuwe positie krijgen
		m_bItemSelected = false;

	}

}

void LevelEditor::PlaatsItem()
{
	//check of het een collisionitem is
	if(LevelEditorGUI::GetSingleton()->GetSelectedCategoryName() == "collision")
	{

		if(m_bCollisionEditing)
		{
			//stopt me editen
			m_bItemSelected = false;
			m_bCollisionEditing = false;
		}else{
			//we moeten ons item nog niet deselecten hier
			m_bItemSelected = true;

			//de eerste afbeelding word geplaatst en onze mousemove
			//bekijkt het verschil in x om te tekenen naar rechts
			m_bCollisionEditing = true;
		}

	}else{
		m_bItemSelected = false;
	}

}

void LevelEditor::HandleRightClicked(hgeInputEvent event)
{
	//delete current selected uit gui
	//we moeten hem ook nog uit onze list halen..

	int id = m_pCurrentLevelItemSelected->GetId();

	//gebruik remove algorithm om iets te verwijderen uit de vector
	std::vector<int>::iterator pos = remove(m_vLevelItems.begin(), m_vLevelItems.end(), m_pCurrentLevelItemSelected->GetId());
	//nog niet verwijdert moeten nog erase doen
															//int sizeA = m_vLevelItems.size();
	m_vLevelItems.erase(pos, m_vLevelItems.end());
	//sizeA = m_vLevelItems.size();

	LevelEditorGUI::GetSingleton()->RemoveButton(id);

	m_pCurrentLevelItemSelected = 0;
	m_bItemSelected = false;
}

bool LevelEditor::Render()
{
	//draw background
	GAME_ENGINE->Gfx_RenderQuad(&m_quad);
	LevelEditorGUI::GetSingleton()->Render();
	return false;
}

void LevelEditor::CreateNewLevelObject(const std::string& objectname)
{
	if(LevelEditorGUI::GetSingleton()->GetSelectedCategoryName() == "collision")
	{
		CreateCollisionItem(objectname);

	}else
	{
		if(LevelEditorGUI::GetSingleton()->GetSelectedCategoryName() == "enemies")
		{
			CreateEnemyItem(objectname);

		}else // we hebben een gewoon background item
		{
		
			//sprite inladen 
			CreateBackGroundItem(objectname);
		}
	
	}
}

void LevelEditor::CreateBackGroundItem(const std::string& objectname)
{
	ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName(objectname);
	const string& slevelobjpath = GameManager::GetSingleton()->GetPath("levelobj");
	string pathtofile = slevelobjpath + "full/" + myStruct.filename;
	LevelItem* levelitem = new LevelItem(GetUniqueLevelId(), m_mouseX, m_mouseY, myStruct.width, myStruct.height, this, false);
	//m_vLevelItems.push_back(levelitem);
	levelitem->Init(pathtofile);
	LevelEditorGUI::GetSingleton()->RegisterNewButton(levelitem);
	LevelItemSelected(levelitem);
	levelitem->SetName(objectname);
	m_bCreated = true;
}

void LevelEditor::CreateEnemyItem(const std::string& objectname)
{
	ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName(objectname);
	const string& slevelobjpath = GameManager::GetSingleton()->GetPath("levelobj");
	string pathtofile = slevelobjpath + "full/" + myStruct.filename;
	EnemyItem* enemyitem = new EnemyItem(GetUniqueLevelId(), m_mouseX, m_mouseY, myStruct.width, myStruct.height, this, false);
	//m_vLevelItems.push_back(levelitem);
	enemyitem->Init(pathtofile);
	LevelEditorGUI::GetSingleton()->RegisterNewButton(enemyitem);
	LevelItemSelected(enemyitem);
	enemyitem->SetName(objectname);
	m_bCreated = true;
}

void LevelEditor::CreateCollisionItem(const std::string& objectname)
{
	//shared stuff
	InitCollisionItemStruct collisionStruct;
	const string& slevelobjpath = GameManager::GetSingleton()->GetPath("levelobj");

	//sprite 1 path maken 
	string objectone = objectname + "start";
	ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName(objectone);
	collisionStruct.width1 = myStruct.width;
	collisionStruct.height1 = myStruct.height;
	string pathtofile1 = slevelobjpath + "full/" + myStruct.filename;

	//sprite 2 path maken
	string objecttwo = objectname + "mid";
	myStruct = GameManager::GetSingleton()->GetFileName(objecttwo);
	collisionStruct.width2 = myStruct.width;
	collisionStruct.height2 = myStruct.height;
	string pathtofile2 = slevelobjpath + "full/" + myStruct.filename;

	//sprite 3 path maken
	string objectthree = objectname + "end";
	myStruct = GameManager::GetSingleton()->GetFileName(objectthree);
	collisionStruct.width3 = myStruct.width;
	collisionStruct.height3 = myStruct.height;
	string pathtofile3 = slevelobjpath + "full/" + myStruct.filename;

	//collision item maken
	LevelCollisionItemComponent* levelitem = new LevelCollisionItemComponent(GetUniqueLevelId(), m_mouseX, m_mouseY, collisionStruct, this, true);
	//m_vLevelItems.push_back(levelitem);
	levelitem->InitCollisionItem(pathtofile1, pathtofile2, pathtofile3);
	levelitem->SetName(objectname);
	LevelEditorGUI::GetSingleton()->RegisterNewButton(levelitem);
	LevelItemSelected(levelitem);
	m_bCreated = true;
}

int LevelEditor::GetUniqueLevelId()
{
	int lastid;
	//check het laatste id van de vector
	if(m_vLevelItems.size() > 0)
	{
		lastid = m_vLevelItems.at(m_vLevelItems.size()-1);
	}else
	{
		lastid = 500;
	}

	//tel er één bij op
	++lastid;

	//voeg toe in de vector
	m_vLevelItems.push_back(lastid);

	//return
	return lastid;
}

void LevelEditor::LevelItemSelected(LevelItem* levelitem)
{
	if(!m_bItemSelected)
	{
		m_pCurrentLevelItemSelected = levelitem;
		m_bItemSelected = true;
		m_bCreated = true;
	}
}

class FSaveToXML
{
public:
	FSaveToXML(std::string& xmlstringtofillin):m_sXMLString(xmlstringtofillin){};
	void operator()(int id)
	{
		hgeGUIObject * pguiobject = LevelEditorGUI::GetSingleton()->GetComponentById(id);
		LevelItem* levelitem = dynamic_cast<LevelItem*>(pguiobject);
		m_sXMLString += levelitem->Save();
	}
private:
	std::string& m_sXMLString;
};


void LevelEditor::WriteXML()
{
	/*
		todo check of bestand bestaat anders moeten we dit nog toevoegen
		string sXMLString("<?xml version=\"1.0\" ?> \" <levels>");
		//weet niet of \n werkt mss via std::endl fixen
	*/
	std::tofstream fout;	
	fout.open("xml/levels.xml",ios::ate | ios::out | ios::in);
	long eindevorigBestand = fout.tellp();
	fout << std::endl << std::endl;
	//voeg level toe aan bestand
	fout << "<level>";
	string sLevelString;
	//save alle level items weg
	for_each(m_vLevelItems.begin(), m_vLevelItems.end(), FSaveToXML(sLevelString));
	fout << sLevelString.c_str();
	fout << "</level>";
	fout << std::endl << std::endl;
	fout << "</levels>";
	fout.flush();

	//vorige closing tag overschrijven met niets </levels> = 9 chars
	fout.seekp((eindevorigBestand-9));
	fout << _T("         ");
	fout.close();

}