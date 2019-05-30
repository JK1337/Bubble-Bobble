//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: ToolComponent
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef TOOLCOMPONENT_H_INCLUDED
#define TOOLCOMPONENT_H_INCLUDED

class ComponentInfo;
class Toolbar;
class ToolArrow;
class ItemInfo;

#include "hge.h"
#include "hgeguictrls.h"
#include "hgegui.h"

#include <vector>
#include "Vector2D.h"
#include "GameManager.h"

enum EnumButtons
{
	NORMAL = 0,
	SELECTED = 1,
	IMAGE = 2,
	LEFTARROW = 3,
	RIGHTARROW = 4
};

class ToolComponent :  public hgeGUIObject {
public:
	ToolComponent(ComponentInfo* info, Toolbar* toolbar);
	virtual ~ToolComponent();
	void Init(int id);
	virtual void Update(float dTime);
	virtual void	Render();
	virtual void	MouseOver(bool bOver);
	virtual bool	MouseLButton(bool bDown);
	virtual void	SetFocus(bool bFocused);
	void ResetSelection();
	void ChooseNewItem(bool bForward);
	void RegisterArrows();
	const string& GetNameCurrentItem() const;
	const string& GetName() const;
private:
	//hgeGUIButton* m_pButtonNormal;
	//hgeGUIButton* m_pButtonSelected;
	hgeSprite* m_pSpr;
	HTEXTURE m_Tex;

	ComponentInfo* m_pComponentInfo;
	hgeGUIButton* m_pButtonNormal;

	vector<hgeGUIButton*> m_vGUIButtons;
	vector<hgeSprite*> m_vGUISprites;
	Vector2D m_vPosition;

	bool m_bSelectedState;
	Toolbar* m_pParent;

	ToolArrow* m_pLeftArrow;
	ToolArrow* m_pRightArrow;

	int m_CurrentSelectedThumb;

	void LoadTexture(const string& texname);
	void SwitchSelectState();
	void ShowNextItem();
	void ShowPreviousItem();
	void LoadArrows(const ToolComponentStruct& myStruct,const ToolComponentStruct& myStructB, double offsetX, double offsetY );
	void LaadImage(const string& imagenaam);
	HTEXTURE GetTexture(const string& texname);
	void LoadAllThumbs();

	vector<hgeSprite*> m_vThumbSprites;


	ToolComponent(const ToolComponent& t);
	ToolComponent& operator=(const ToolComponent& t);
	

};

#endif