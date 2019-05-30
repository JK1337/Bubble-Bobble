//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUI
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "..\include\hge.h"
#include "..\include\hgegui.h"

class GUI {
public:
	GUI();
	virtual ~GUI();
	void Init();
	bool Update(float dTime);
	bool Render();
private:
	hgeGUI     *m_pGui;
	hgeSprite  *m_pSprCursor;
	HTEXTURE   m_TextureCursor;
	GUI(const GUI& t);
	GUI& operator=(const GUI& t);

	void CreateControls();


};

#endif