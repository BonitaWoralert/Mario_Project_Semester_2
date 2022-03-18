#include "PowBlock.h"


PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str()));
	{
		std::cout << "Failed to load texture." << std::endl;
		return;
	}

	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3; //3 images in this sprite sheet
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}
PowBlock::~PowBlock()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	m_level_map = nullptr;
}
void PowBlock::Render()
{

}
void PowBlock::TakeHit()
{
	m_num_hits_left -= 1;
	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}