//-----------------------------------------------------------------
// Parser Include Files
//-----------------------------------------------------------------
#include "stdafx.h"
#include "XMLParser.h"
#include "expatpp.cpp"




//-----------------------------------------------------------------
// Extra Include Files

//default game
#include "GameSettings.h"
#include "CharacterSetting.h"
#include "AnimationSetting.h"
#include "SpriteSheetSetting.h"

////------------------------------------------------------------////

//gui
#include "GuiSettings.h"
#include "ComponentInfo.h"
#include "ItemInfo.h"
#include "GameManager.h"
#include "CollisionItemInfo.h"

//level
#include "LevelData.h"
#include "LevelSettings.h"
#include "ItemData.h"
#include "CollisionData.h"

//-----------------------------------------------------------------
//----------------------------------------------------------------
/*
DEFAULT SETTINGS XML PARSER
*/
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// XMLParser constructor(s)																				
//-----------------------------------------------------------------

XMLParser::XMLParser(GameSettings* mySettings) : m_pGameSettings(mySettings)
{
	// nothing to create
}
//-----------------------------------------------------------------
// XMLParser methods																			
//-----------------------------------------------------------------
void XMLParser::startElement(const XML_Char* name, const XML_Char** atts)
{	
	// this method fires for an opening tag	

	if (tstring(name) == _T("character"))
	{
		//we maken een nieuw karakter aan
		CharacterSetting* pcharacter = new CharacterSetting();
		//setting->SetName()
			tstring attname;
			int i = 0;
			while (atts[i] != NULL)
			{
				if (i % 2 == 0)
					attname = tstring(atts[i]);
				else
				{
					if (attname == _T("name"))
						pcharacter->SetName(tstring(atts[i]));
					else if (attname == _T("speed"))
						pcharacter->SetSpeed(ParseFloat(tstring(atts[i])));
					else if(attname == _T("startframe"))
						pcharacter->SetStartAnimation(tstring(atts[i]));
					else if(attname== _T("startanimation"))
						pcharacter->SetStartAnimation(tstring(atts[i]));
				}
				++i;
			}
		m_pGameSettings->AddCharacter(pcharacter);
	}

	else if(tstring (name) == _T("animation"))
	{
		//maak een animation en voeg toe aan huidig karakter
		AnimationSetting* panimsetting = new AnimationSetting();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					panimsetting->SetAnimationName(tstring(atts[i]));
				else if (attname == _T("frames"))
					panimsetting->SetNumFrames(ParseInt(tstring(atts[i])));
				else if (attname == _T("startframe"))
					panimsetting->SetStartFrame(ParseInt(tstring(atts[i])));
				else if (attname == _T("loop"))
					panimsetting->SetLoop(ParseBoolean(tstring(atts[i])));
				else if (attname == _T("backtoidle"))
					panimsetting->SetBackToIdle(ParseBoolean(tstring(atts[i])));
				else if (attname == _T("play"))
					panimsetting->SetPlay(ParseBoolean(tstring(atts[i])));
				else if (attname == _T("row"))
					panimsetting->SetRow(ParseInt(tstring(atts[i])));
			}
			++i;
		}
	
		//voeg de nieuwe animatie toe aan laatst aangemaakte karakter
		m_pGameSettings->EditLastCharacter()->AddAnimation(panimsetting);
	}

	else if(tstring (name) == _T("spritesheet"))
	{
		//maak een animation en voeg toe aan huidig karakter
		SpriteSheetSetting* pspritesheetsetting = new SpriteSheetSetting();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("partheight"))
					pspritesheetsetting->SetRowHeight(ParseFloat(tstring(atts[i])));
				else if (attname == _T("partwidth"))
						pspritesheetsetting->SetRowWidth(ParseFloat(tstring(atts[i])));
				else if (attname == _T("midX"))
						pspritesheetsetting->SetMidX(ParseFloat(tstring(atts[i])));
				else if (attname == _T("midY"))
						pspritesheetsetting->SetMidY(ParseFloat(tstring(atts[i])));
				else if(attname == _T("type"))
						pspritesheetsetting->SetType(tstring(atts[i]));
			}
			++i;
		}

		//voeg de nieuwe animatie toe aan laatst aangemaakte karakter
		m_pGameSettings->EditLastCharacter()->SetSpriteSheetSetting(pspritesheetsetting);
	}

}

void XMLParser::endElement(const XML_Char* s)
{	
	
}

void XMLParser::charData(const XML_Char *s, int len)
{

}


//-----------------------------------------------------------------
//
//
//-----------------------------------------------------------------
/*
			NON MEMBER FUNCTIONS
*/
//-----------------------------------------------------------------

int ParseInt(const tstring& value) 
{
	int result;
	tstringstream tss(value);
	tss>>result;
	return result;
}

float ParseFloat(const tstring& value) 
{
	float result;
	tstringstream tss(value);
	tss>>result;
	return result;
}

bool ParseBoolean(const tstring& value) 
{
	bool result;
	tstringstream tss(value);
	tss>>result;
	return result;
}

std::string ToStdString( const tstring& value ) 
{
	string s(value.begin(), value.end());
	s.assign(value.begin(), value.end());
	return s;
}




//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------













//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
/*
			XML PARSER GUI
*/
//-----------------------------------------------------------------

XMLParserGUI::XMLParserGUI( GuiSettings* mysettings ):m_pGuiSettings(mysettings)
{

}


void XMLParserGUI::startElement(const XML_Char* name, const XML_Char** atts)
{	
	// this method fires for an opening tag	
	if (tstring(name) == _T("category"))
	{
		//we maken een nieuw karakter aan
		m_pCurrentComponent = new ComponentInfo();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					m_pCurrentComponent->SetName(ToStdString(tstring(atts[i])));
				else if (attname == _T("id"))
					m_pCurrentComponent->SetId(ParseInt(tstring(atts[i])));
			}
			++i;
		}


	}

	else if(tstring (name) == _T("Item"))
	{
		ItemInfo* item = new ItemInfo();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					item->SetNaam(ToStdString(tstring(atts[i])));
				else if (attname == _T("id"))
					item->SetId(ParseInt(tstring(atts[i])));
			}
			++i;
		}

		m_pCurrentComponent->AddItemInfo(item);
	}

	else if(tstring (name) == _T("CollisionItem"))
	{
		//maak huidig collision item aan
		m_pCurrentCollisionItem = new CollisionItemInfo();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					m_pCurrentCollisionItem->SetName(ToStdString(tstring(atts[i])));
			}
			++i;
		}
	}

	else if(name == _T("SubItem"))
	{
		ItemInfo* item = new ItemInfo();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					item->SetNaam(ToStdString(tstring(atts[i])));
				else if (attname == _T("id"))
					item->SetId(ParseInt(tstring(atts[i])));
			}
			++i;
		}

		m_pCurrentCollisionItem->AddItemInfo(item);
	}
 
	else if(tstring (name) == _T("path"))
	{
		tstring attname;
		string name;
		string path;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("typename"))
					name = ToStdString(tstring(atts[i]));
				else if (attname == _T("path"))
					path = ToStdString(tstring(atts[i]));
			}
			++i;
		}

		GameManager::GetSingleton()->AddPath(std::make_pair(name,path));
		
	}

	else if(tstring(name) == _T("filename"))
	{
		tstring attname;

		ToolComponentStruct mystruct;

		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					mystruct.name = ToStdString(tstring(atts[i]));
				else if (attname == _T("filename"))
					mystruct.filename = ToStdString(tstring(atts[i]));
				else if (attname == _T("width"))
					mystruct.width = ParseFloat(tstring(atts[i]));
				else if (attname == _T("height"))
					mystruct.height = ParseFloat(tstring(atts[i]));
			}
			++i;
		}

		GameManager::GetSingleton()->AddFileName(mystruct);
	}

}

void XMLParserGUI::endElement(const XML_Char* s)
{	
	if(tstring(s) == _T("category"))
		m_pGuiSettings->AddComponentInfo(m_pCurrentComponent);

	if(tstring(s) == _T("CollisionItem"))
		m_pGuiSettings->AddCollisionItem(m_pCurrentCollisionItem);
}

void XMLParserGUI::charData(const XML_Char *s, int len)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------










//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
/*
XML PARSER LEVEL
*/
//-----------------------------------------------------------------

XMLParserLevel::XMLParserLevel(LevelSettings* mysettings):m_pLevelSettings(mysettings)
{

}


void XMLParserLevel::startElement(const XML_Char* name, const XML_Char** atts)
{	
	// this method fires for an opening tag	
	if (tstring(name) == _T("level"))
	{
		//we maken een nieuw karakter aan
		m_pCurrentLevel = new LevelData();

		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				//if (attname == _T("name"))
					
					//m_pCurrentLevel->SetName(ToStdString(tstring(atts[i])));
			}
			++i;
		}
	}

	// this method fires for an opening tag	
	else if (tstring(name) == _T("CollisionItem"))
	{
		//we maken een nieuw karakter aan
		CollisionData* pCollisiondata = new CollisionData();


		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					pCollisiondata->SetName(ToStdString(tstring(atts[i])));
				else if(attname == _T("x"))
					pCollisiondata->SetX(ParseFloat(tstring(atts[i])));
				else if(attname == _T("y"))
					pCollisiondata->SetY(ParseFloat(tstring(atts[i])));
				else if(attname == _T("aantalMid"))
					pCollisiondata->SetAantalWidth(ParseFloat(tstring(atts[i])));
				else if(attname == _T("width"))
					pCollisiondata->SetWidth(ParseFloat(tstring(atts[i])));
				else if(attname == _T("height"))
					pCollisiondata->SetHeight(ParseFloat(tstring(atts[i])));
			}
			++i;
		}

		m_pCurrentLevel->AddCollisionData(pCollisiondata);
	}

	// this method fires for an opening tag	
	else if (tstring(name) == _T("levelItem"))
	{
		//we maken een nieuw karakter aan
		ItemData* pItemdata = new ItemData();


		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					pItemdata->SetName(ToStdString(tstring(atts[i])));
				else if(attname == _T("x"))
					pItemdata->SetX(ParseFloat(tstring(atts[i])));
				else if(attname == _T("y"))
					pItemdata->SetY(ParseFloat(tstring(atts[i])));
				else if(attname == _T("width"))
					pItemdata->SetWidth(ParseFloat(tstring(atts[i])));
				else if(attname == _T("height"))
					pItemdata->SetHeight(ParseFloat(tstring(atts[i])));
			}
			++i;
		}

		m_pCurrentLevel->AddItemData(pItemdata);
	}

	else if (tstring(name) == _T("enemyItem"))
	{
		//we maken een nieuw karakter aan
		ItemData* pItemdata = new ItemData();


		tstring attname;
		int i = 0;
		while (atts[i] != NULL)
		{
			if (i % 2 == 0)
				attname = tstring(atts[i]);
			else
			{
				if (attname == _T("name"))
					pItemdata->SetName(ToStdString(tstring(atts[i])));
				else if(attname == _T("x"))
					pItemdata->SetX(ParseFloat(tstring(atts[i])));
				else if(attname == _T("y"))
					pItemdata->SetY(ParseFloat(tstring(atts[i])));
				else if(attname == _T("width"))
					pItemdata->SetWidth(ParseFloat(tstring(atts[i])));
				else if(attname == _T("height"))
					pItemdata->SetHeight(ParseFloat(tstring(atts[i])));
			}
			++i;
		}

		m_pCurrentLevel->AddEnemyData(pItemdata);
	}




}

void XMLParserLevel::endElement(const XML_Char* s)
{	
	if(tstring(s) == _T("level"))
		m_pLevelSettings->AddLevelData(m_pCurrentLevel);
}

void XMLParserLevel::charData(const XML_Char *s, int len)
{

}
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------


