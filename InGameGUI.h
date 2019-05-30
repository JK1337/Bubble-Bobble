//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: InGameGUI
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef InGameGUI_H_INCLUDED
#define InGameGUI_H_INCLUDED

#include "..\include\hge.h"
#include "..\include\hgeGUI.h"

class InGameGUI {
public:
	InGameGUI();
	virtual ~InGameGUI();
	void Init();
	bool Update(float dTime);
	bool Render();
private:
	hgeGUI     *m_pInGameGUI;
	hgeSprite  *m_pSprCursor;
	HTEXTURE   m_TextureCursor;
	InGameGUI(const InGameGUI& t);
	InGameGUI& operator=(const InGameGUI& t);

	void CreateControls();


};

#endif