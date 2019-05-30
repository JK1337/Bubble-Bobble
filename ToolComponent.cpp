//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ToolComponent
//							  Date: 23/7/2009
//******************************************************************************************

#include "stdafx.h"
#include "ToolComponent.h"
#include "ComponentInfo.h"
#include "GameManager.h"
#include "LevelEditorGUI.h"
#include "Toolbar.h"
#include "MyGameDefines.h"
#include "ToolArrow.h"
#include "ItemInfo.h"
#include <algorithm>

ToolComponent::ToolComponent(ComponentInfo* info, Toolbar* parent):m_pComponentInfo(info), m_bSelectedState(false),
																	m_pParent(parent),m_CurrentSelectedThumb(0)
{
	bStatic=false; bVisible=true; bEnabled=true;
}


ToolComponent::~ToolComponent(){
	delete m_pSpr;
	delete m_pButtonNormal;
	delete m_pComponentInfo;
	delete m_pLeftArrow;
	delete m_pRightArrow;
	GAME_ENGINE->Texture_Free(m_Tex);
}

void ToolComponent::Init(int id)
{
	this->id = id;
	
	m_vPosition.x = 0;
	m_vPosition.y = ((id-1)*52.0f);

	//Images Inladen
	LaadImage("normaalKader");
	LaadImage("selectedKader");

	//Creeer Pijltjes
	ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName("rightArrow");
	int bordersize(2);
	double offsetX = m_vGUISprites.at(0)->GetWidth() - myStruct.width;
	double offsetY = m_vGUISprites.at(0)->GetHeight() - myStruct.height;
	LoadArrows(myStruct, GameManager::GetSingleton()->GetFileName("leftArrow"), bordersize, offsetY);
	

	//we maken onze rect van deze knop kleiner dan de buttons van de pijl
	/*
			------------- offsetY
			<< BUTTON >>
			   
			  |
		   offsetX
	*/
	
	rect.Set(static_cast<float>(m_vPosition.x+bordersize+myStruct.width),
		static_cast<float>(m_vPosition.y + offsetY / 2.0f), 
		static_cast<float>(m_vPosition.x+m_vGUISprites.at(0)->GetWidth()-(bordersize+myStruct.width)),
		static_cast<float>(m_vPosition.y+myStruct.height));

	LoadAllThumbs();
	//LoadTexture("Tools/kaderselected.png");
	//m_pButtonNormal = new hgeGUIButton(id,x,y,width,height,m_Tex,0,0);
	//LevelEditorGUI::GetSingleton()->RegisterNewButton(m_pButtonNormal);
}

void ToolComponent::RegisterArrows()
{
	LevelEditorGUI::GetSingleton()->RegisterNewButton(m_pLeftArrow);
	LevelEditorGUI::GetSingleton()->RegisterNewButton(m_pRightArrow);
}

void ToolComponent::LaadImage(const string& imagenaam)
{
	ToolComponentStruct myStruct = GameManager::GetSingleton()->GetFileName(imagenaam);
	LoadTexture(myStruct.filename);
	m_pSpr = new hgeSprite(m_Tex, static_cast<float>(m_vPosition.x), static_cast<float>(m_vPosition.y), static_cast<float>(myStruct.width), static_cast<float>(myStruct.height));
	m_vGUISprites.push_back(m_pSpr);
}



void ToolComponent::Update( float dTime )
{
	//m_pButtonNormal->
}



void ToolComponent::LoadTexture(const string& texname)
{
	//todo parent name vergelijken om extra path nog goe in te vulle
	//string extrapath = GameManager::GetSingleton()->GetArtPath();
	string extrapath = GameManager::GetSingleton()->GetPath("tools");
	string pathname = GameManager::GetSingleton()->GetArtPath();
	string pathtotexture = pathname + extrapath + texname;
	m_Tex= GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());
}

HTEXTURE ToolComponent::GetTexture(const string& texname)
{
	//todo parent name vergelijken om extra path nog goe in te vulle
	//string extrapath = GameManager::GetSingleton()->GetArtPath();
	string extrapath = GameManager::GetSingleton()->GetPath("tools");
	string pathname = GameManager::GetSingleton()->GetArtPath();
	string pathtotexture = pathname + extrapath + texname;
	return GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());
}

void ToolComponent::MouseOver( bool bOver )
{
	if(bOver) gui->SetFocus(id);
}

bool ToolComponent::MouseLButton( bool bDown )
{
	if(!bDown)
	{
		
		return true;
	}
	else 
	{
		SwitchSelectState();
		//hge->Effect_Play(snd);
		//offset=0;
		
		return false;
	}
}

void ToolComponent::SwitchSelectState()
{
	m_pParent->SetSelected(this);
	m_bSelectedState = !m_bSelectedState;
}

void ToolComponent::Render()
{
	float xPos = static_cast<float>(m_vPosition.x);
	float yPos = static_cast<float>(m_vPosition.y);

	if(m_bSelectedState)
		m_vGUISprites.at(1)->Render(xPos,yPos);
	else
		m_vGUISprites.at(0)->Render(xPos,yPos);
	
	//xpos & ypos moeten ofzet krijgen voor de image:
	//ongeveer de breedte van de border + bar voor x

	//de hoogte van de border voor y
	xPos += 12;
	yPos += 2;

	m_vThumbSprites.at(m_CurrentSelectedThumb)->Render(xPos, yPos);
}

void ToolComponent::SetFocus(bool bFocused)
{
	int kak = 0;
}

void ToolComponent::ResetSelection()
{
	m_bSelectedState = false;
}

const string& ToolComponent::GetName() const
{
	return m_pComponentInfo->GetName();
}

void ToolComponent::ChooseNewItem(bool bForward)
{
	if(bForward) //volgend item kiezen
		ShowNextItem();
	else
		ShowPreviousItem();
}

void ToolComponent::ShowNextItem()
{
	++m_CurrentSelectedThumb;
		if(m_CurrentSelectedThumb == m_vThumbSprites.size())
			m_CurrentSelectedThumb  = 0;
}

void ToolComponent::ShowPreviousItem()
{
	--m_CurrentSelectedThumb;
	if(m_CurrentSelectedThumb<0)
		m_CurrentSelectedThumb = m_vThumbSprites.size() -1;
}

void ToolComponent::LoadArrows( const ToolComponentStruct& myStruct,const ToolComponentStruct& myStructB, double offsetX, double offsetY)
{
	float thisTotalWidth = m_vGUISprites.at(0)->GetWidth();
	float ydif = static_cast<float>(this->m_vPosition.y);
	m_pLeftArrow = new ToolArrow(id*10, offsetX, offsetY/2.0f + ydif  , 
		myStruct.width, myStruct.height, 
		this, false);
	m_pRightArrow = new ToolArrow(id*10+1, thisTotalWidth-myStructB.width-offsetX, 
		offsetY/2.0f + ydif , 
		myStructB.width, myStructB.height, 
		this, true);

	const string& stoolpath = GameManager::GetSingleton()->GetPath("tools");
	m_pLeftArrow->Init(stoolpath + GameManager::GetSingleton()->GetFileName("leftArrow").filename);
	m_pRightArrow->Init(stoolpath + GameManager::GetSingleton()->GetFileName("rightArrow").filename);
}

class FCreateThumb
{
public:
	FCreateThumb(std::vector<hgeSprite*>& tofillin,const std::string& spath):m_vToFill(tofillin),m_sPath(spath){};
	void operator()(ItemInfo* info)
	{
		string pathtotexture = m_sPath + info->GetNaam() + ".png";
		HTEXTURE tex = GameManager::GetSingleton()->GetGameEngine()->Texture_Load(pathtotexture.c_str());

		hgeSprite* spr = new hgeSprite(tex, 0, 0, 80, 48);
		m_vToFill.push_back(spr);
	}
private:
	std::vector<hgeSprite*>& m_vToFill;
	const std::string& m_sPath;
};

void ToolComponent::LoadAllThumbs()
{
	string path = GameManager::GetSingleton()->GetArtPath() +	GameManager::GetSingleton()->GetPath("levelobj") + "thumbs/";
	for_each(m_pComponentInfo->GetItemInfos().begin(), m_pComponentInfo->GetItemInfos().end(), FCreateThumb(m_vThumbSprites, path));
}

const string& ToolComponent::GetNameCurrentItem() const
{
	return m_pComponentInfo->GetItemInfos().at(m_CurrentSelectedThumb)->GetNaam();
}