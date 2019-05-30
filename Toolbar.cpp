//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Toolbar
//							  Date: 23/7/2009
//******************************************************************************************
#include "stdafx.h"
#include "Toolbar.h"
#include "GuiSettings.h"
#include "ToolComponent.h"
#include "GUIComponent.h"
#include <algorithm>
#include "LevelEditorGUI.h"
#include "LevelEditor.h"
using namespace std;

Toolbar::Toolbar(GuiSettings* guisettings, double width, double height,LevelEditor* editor):m_pGuiSettings(guisettings), m_vecPos(0,0),BaseEntity(m_vecPos, width, height),
						m_pCurrentSelectedComponent(0),m_pLevelEditor(editor)
{

}

Toolbar::~Toolbar()
{

}

void Toolbar::Init()
{
	CreateComponents();
}

class FCreateComponent
{
public:
	FCreateComponent(vector<ToolComponent*>& vToFill, Toolbar* thisisme):m_vToVec(vToFill)
															,m_Counter(0)
															,m_This(thisisme){};
	void operator()(ComponentInfo* componentinfo)
	{
		ToolComponent* component = new ToolComponent(componentinfo,m_This);
		component->Init(++m_Counter);

		//todo misschien is het niet nodig ze extra bij te houden
		//aangezien we proberen om alles via het gui systeem up te daten
		//later nog herzien!
		m_vToVec.push_back(component);

		LevelEditorGUI::GetSingleton()->RegisterNewButton(component);

		//nu nog een post init om de andere 2 pijltjes te registreren
		component->RegisterArrows();
	}
private:
	int m_Counter;
	Toolbar* m_This;
	vector<ToolComponent*>& m_vToVec;
};

void Toolbar::CreateComponents()
{
	//voor elke category in onze gui settings maken we een knop aan
	/*
		vector iterators incompatible :s

		//onderste methode werkt uiteindelijk wel als ik een kopie maak van de vector!?!
		//ik kon niet aan de vector via de methode GetAllComponentInfo() anders waren de iterators fout..
	*/ 
	std::vector<ComponentInfo*>::iterator myIt;
	//constbyrefcopy
	const std::vector<ComponentInfo*>& myComponentInfo = m_pGuiSettings->GetAllComponentInfo();
	for_each(myComponentInfo.begin(), myComponentInfo.end(), FCreateComponent(m_vGuiComponents, this));	 
}


class FUpdateComponent
{
public:
	FUpdateComponent(float dTime):m_fdTime(dTime){};
	void operator()(ToolComponent* component)
	{
		component->Update(m_fdTime);
	}
private:
	float m_fdTime;
};

bool Toolbar::Update( float dTime )
{
	//voor elke category in onze gui doen we een update
	for_each(m_vGuiComponents.begin(), m_vGuiComponents.end(), FUpdateComponent(dTime));
	return true;
}

class FRenderComponent
{
public:
	FRenderComponent(){};
	void operator()(ToolComponent* component)
	{
		component->Render();
	}
private:
	
};


bool Toolbar::Draw()
{
	//voor elke category in onze gui doen we een update
	for_each(m_vGuiComponents.begin(), m_vGuiComponents.end(), FRenderComponent());
	return true;
}

void Toolbar::SetSelected(ToolComponent* newselected)
{
	if(m_pCurrentSelectedComponent != 0)
		m_pCurrentSelectedComponent->ResetSelection();

	m_pCurrentSelectedComponent = newselected;

	//hang sprite aan de muis
	m_pLevelEditor->CreateNewLevelObject(m_pCurrentSelectedComponent->GetNameCurrentItem());
}

const string& Toolbar::GetSelectedCategoryName() const
{
	return m_pCurrentSelectedComponent->GetName();
}

