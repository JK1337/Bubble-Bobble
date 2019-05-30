//******************************************************************************************
//							Author: Jasper Kindt
//							 Class: Application
//							  Date: 10/7/2009
//******************************************************************************************

#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

class HGE;


class Application {
public:
	Application();
	virtual ~Application();
	//bool FrameFunc();
	int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd );

private:
	
	Application(const Application& t);
	Application& operator=(const Application& t);
};
HGE * GAME_ENGINE = 0;
bool FrameFunc();
#endif