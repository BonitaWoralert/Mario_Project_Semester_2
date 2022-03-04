#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete luigi;
	delete mario;
	luigi = nullptr;
	mario = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//draw character
	mario->Render();
	luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//set up player character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(90, 330));
}