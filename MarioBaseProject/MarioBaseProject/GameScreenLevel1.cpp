#include "GameScreenLevel1.h"
#include <iostream>
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	m_level_map = nullptr;
	m_countdown = 2.0f;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete luigi;
	delete mario;
	delete m_pow_block;
	m_pow_block = nullptr;
	luigi = nullptr;
	mario = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//draw enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw character
	m_pow_block->Render();
	mario->Render();
	luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//screen shake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	//update character
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	if (Collisions::Instance()->Circle(mario, luigi))
	{
		//std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		//std::cout << "Box hit!" << std::endl;
	}
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

	//set up map
	SetLevelMap();
	//set up pow 
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	//set up characters
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330),
		m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(90, 330),
		m_level_map);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
	//clear old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set new map!
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	m_countdown -= deltaTime;
	if (m_countdown <= 0)
	{
		CreateKoopa(Vector2D(rand() % SCREEN_WIDTH + 1, 32), FACING(rand() & 1), KOOPA_SPEED);
		m_countdown = 2.0f;
	}

	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if enemy is on bottom row
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is enemy off screen to left/right? 
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width
					* 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH -
					(float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					//m_enemies[i]->Turn();
					m_enemies[i]->SetAlive(false);
				}
			}
			//now do update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]
				->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f
					|| m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
					}
				}
			}

			//if enemy is no longer alive then schedule for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position,
		m_level_map, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (((Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox())) || 
		(Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))) 
		&& m_pow_block != nullptr)
	{
		//collided while jumping
		if (mario->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			mario->CancelJump();	
		}
		else if (luigi->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			luigi->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}