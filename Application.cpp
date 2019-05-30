#include "hge.h"
#include "Game.h"
#include "GameManager.h"

HGE *GAME_ENGINE = 0;
Game* GAME = 0;

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
// just check whether ESC key has been pressed.
bool FrameFunc()
{
	// By returning "true" we tell HGE
	// to stop running the application.
	if (GAME_ENGINE->Input_GetKeyState(HGEK_ESCAPE)) return true;


	//update all
	float dt=GAME_ENGINE->Timer_GetDelta();
	GAME->Update(dt);

	// Continue execution
	return false;
}

bool RenderFunc()
{
	
	GAME_ENGINE->Gfx_BeginScene();
	GAME_ENGINE->Gfx_Clear(ARGB(1, 0, 0, 0.8));
	
	GAME->Render();

	GAME_ENGINE->Gfx_EndScene();

	return false;
}

void StartGame()
{
	GameManager::GetSingleton()->SetGameEngine(GAME_ENGINE);
	GAME = new Game();
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Here we use global pointer to HGE interface.
	// Instead you may use hgeCreate() every
	// time you need access to HGE. Just be sure to
	// have a corresponding hge->Release()
	// for each call to hgeCreate()
	GAME_ENGINE = hgeCreate(HGE_VERSION);

	// Set our frame function
	GAME_ENGINE->System_SetState(HGE_FRAMEFUNC, FrameFunc);

	//Set our render function 
	GAME_ENGINE->System_SetState(HGE_RENDERFUNC, RenderFunc);

	//Set FPS 
	GAME_ENGINE->System_SetState(HGE_FPS, 24);
	float screenheight = 1024;
	float screenwidth = 1024;
	GAME_ENGINE->System_SetState(HGE_SCREENWIDTH, screenwidth);
	GAME_ENGINE->System_SetState(HGE_SCREENHEIGHT, screenheight);
	GameManager::GetSingleton()->SetScreenHeight(screenheight);
	GameManager::GetSingleton()->SetScreenWidth(screenwidth);

	GAME_ENGINE->System_SetState(HGE_ZBUFFER, true);

	// Set the window title
	GAME_ENGINE->System_SetState(HGE_TITLE, "It's Bubble Bobble time!");

	// Run in windowed mode
	// Default window size is 800x600
	GAME_ENGINE->System_SetState(HGE_WINDOWED, true);

	// Don't use BASS for sound
	GAME_ENGINE->System_SetState(HGE_USESOUND, false);

	// Tries to initiate HGE with the states set.
	// If something goes wrong, "false" is returned
	// and more specific description of what have
	// happened can be read with System_GetErrorMessage().
	if(GAME_ENGINE->System_Initiate())
	{
		StartGame();
		// Starts running FrameFunc().
		// Note that the execution "stops" here
		// until "true" is returned from FrameFunc().
		GAME_ENGINE->System_Start();
	}
	else
	{	
		// If HGE initialization failed show error message
		MessageBoxA(NULL, GAME_ENGINE->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	// Now ESC has been pressed or the user
	// has closed the window by other means.

	// Restore video mode and free
	// all allocated resources
	GAME_ENGINE->System_Shutdown();

	// Release the HGE interface.
	// If there are no more references,
	// the HGE object will be deleted.
	GAME_ENGINE->Release();

	return 0;
}
