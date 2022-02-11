#include "Texture2D.h"
#include "SDL_image.h"
#include <iostream>

//https://www.aliexpress.com/item/4000785103018.html?spm=a2g0o.seodetail.topbuy.1.1efbff38oiDpz2

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
Texture2D::~Texture2D()
{

}

bool Texture2D::LoadFromFile(std::string path)
{

}
void Texture2D::Free()
{

}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{

}
