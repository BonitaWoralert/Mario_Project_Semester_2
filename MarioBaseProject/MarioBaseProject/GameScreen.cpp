#include "GameScreen.h"
#include <iostream>

//#include <SDL_image.h>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render(){}
void GameScreen::Update(float deltaTime, SDL_Event e){}