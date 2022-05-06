// https://gigi.nullneuron.net/gigilabs/animations-with-sprite-sheets-in-sdl2/ 
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

//Globals 
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
//Texture2D* g_texture = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;
Mix_Chunk* g_sfx = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(std::string path);

int main(int argc, char* args[])
{	
	//Check sdl setup correctly
	if (InitSDL())
	{
		LoadMusic("Audio/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set time
		g_old_time = SDL_GetTicks();
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
	//initialise audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Mixer could not init. Error: " << Mix_GetError();
		return false;
	}

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

		
	}
}

void CloseSDL()
{
	//destroy game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//clear music
	Mix_FreeMusic(g_music);
	g_music = nullptr;

	//release renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Update()
{
	//time
	Uint32 new_time = SDL_GetTicks();

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
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			//press button to quit
		case SDLK_ESCAPE:
			return true;
			break;
		}
		break;
	}

	
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}
void Render()
{
	//Clear screen 
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Update the screen
	SDL_RenderPresent(g_renderer);
}

void LoadMusic(std::string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
	}
}