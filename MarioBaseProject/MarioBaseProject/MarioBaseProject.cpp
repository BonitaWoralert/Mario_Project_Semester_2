// MarioBaseProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"


//Globals 
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(std::string path);
void FreeTexture();

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
			Render();
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

		//create renderer
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		//did renderer get created?
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			std::cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		//Load background texture
		g_texture = LoadTextureFromFile("Images/test.bmp");
		if (g_texture == nullptr)
		{
			return false;
		}
	}
}
void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//clear the texture
	FreeTexture();
	//release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

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
void Render()
{
	//Clear screen 
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	//Where to render texture
	SDL_Rect renderLocation = { 0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT };

	//Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	//Update the screen
	SDL_RenderPresent(g_renderer);
}
SDL_Texture* LoadTextureFromFile(std::string path)
{
	//remove memory from previous texture
	FreeTexture();
	SDL_Texture* p_texture = nullptr;

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		//create texture from pixels on surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr)
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		//remove loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	//Return the texture
	return p_texture;
}
void FreeTexture()
{
	//check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}