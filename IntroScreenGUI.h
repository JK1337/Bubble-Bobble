//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUI
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "..\include\hge.h"
#include "..\include\hgegui.h"

class IntroScreenGUI {
public:
	IntroScreenGUI();
	virtual ~IntroScreenGUI();
	void Init();
	bool Update(float dTime);
	bool Render();
private:
	hgeGUI     *m_pGui;
	hgeSprite  *m_pSprCursor;
	HTEXTURE   m_TextureCursor;
	IntroScreenGUI(const IntroScreenGUI& t);
	IntroScreenGUI& operator=(const IntroScreenGUI& t);

	void CreateControls();


};

#endif