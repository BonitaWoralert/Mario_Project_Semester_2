// MarioBaseProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"


//Globals 
SDL_Window* g_window = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[])
{

	//Check sdl setup correctly
	if (InitSDL())
	{
		//flag to see if user wants to quit
		bool quit = false;
		
		//Game Loop
		while (!quit)
		{
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Click the X or press Enter to quit!",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did window get created?
		if (g_window == nullptr)
		{
			//window failed
			std::cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
}
void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Update()
{
	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}

	switch (e.key.keysym.sym)
	{
		//press button to quit
	case SDLK_RETURN:
		return true;
		break;
	}

	return false;
}