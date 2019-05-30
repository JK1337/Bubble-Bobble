//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: GUIComponent
//							  Date: 23/7/2009
//******************************************************************************************

#ifndef GUICOMPONENT_H_INCLUDED
#define GUICOMPONENT_H_INCLUDED




class GUIComponent {
public:
	GUIComponent();
	virtual ~GUIComponent();
	void Init();
private:

	GUIComponent(const GUIComponent& t);
	GUIComponent& operator=(const GUIComponent& t);
};

#endif